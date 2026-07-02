
# 多人聊天室


功能实现：
1. 已实现功能

- 输入`quit`退出
- 无客户端连接（1分钟）后退出
- 支持多语言输入
- 高并发连接 (v2.0实现)

2. 待完成功能

- 可发送文件、图片等信息
- 可进行语言翻译
- 补充 ctrl+c 退出


## 1. 预备知识

### 1.1 select()

`select()`可同时监听多个 sockets，可通知程序哪些 sockets 有数据可以读取，哪些 sockets 可以写入。
> 类似的还有 poll()、epoll()

#### 1.1.1 基本语法

```c
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

// 该函数通过 readfds、writefds、exceptfds 监听文件描述符的 sets
// 若可读取某个文件描述符，只需将 sockfd 新增到 readfds 中
// numfds 需设置为文件描述符的最高值加 1

int select(int numfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
```

当`select()`返回时，readfds 会被修改，用来反映设置的文件描述符中有哪些数据可以读取。可使用下述的`FD_ISSET()`宏来获取可读的文件描述符。

```c
FD_SET(int fd, fd_set *set); // 将 fd 新增到 set
FD_CLR(int fd, fd_set *set); // 从 set 中移除 fd
FD_ISSET(int fd, fd_set *set); // 若 fd 在 set 中，返回 true
FD_ZERO(fd_set *set); // 将 set 整个清为 0
```

`select()`同时可通过结构体`struct timeval`来设置 timeout 的周期：

```c
struct timeval{
    int tv_sec; // 秒
    int tv_usec; // 微秒
}
```


### 1.2 epoll

`select()`最多同时监听 1024 个fd，这是由宏`_FD_SETSIZE`决定的，虽然可以通过修改头文件再重新编译来扩大监听数目，但是治标不治本。并且随着 fd 数目的增加，其效率也会随之下降。

而`epoll`采用红黑树管理文件描述符，不会随着监听 fd 数目的增长而降低效率。`epoll`有三个基本函数：


1. epoll_create()

```c
// size - 指定监听数目大小
// 返回 epoll 专用的文件描述符
int epoll_create(int size);
```

2. epoll_ctl()

`epoll`的事件注册函数，注册要监听的事件类型。

```c
/* 
epfd - epoll_create()函数的返回值
op - 表示动作，用三个宏来表示
    EPOLL_CTL_ADD - 注册新的 fd 到 epfd 中
    EPOLL_CTL_MOD - 修改已经注册的 fd 监听事件
    EPOLL_CTL_DEL - 从 epfd 中删除一个 fd
fd - 需要监听的文件描述符
event - 指定内核要监听什么事件
*/
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
```

events 可以是以下宏的集合：
- EPOLLIN：表示对应的 fd 可以读
- EPOLLOUT：表示对应的 fd 可以写
- EPOLLPRI：表示对应的 fd 有紧急的数据可读
- EPOLLERR：表示对应的 fd 发生错误
- EPOLLHUP：表示对应的 fd 被挂断
- EPOLLET：将 epoll 设为边缘触发模式
- EPOLLONESHOT：只监听一次事件

3. epoll_wait()

等待事件的产生，收集在 epoll 监控的事件中已经发生的事件。

```c
// maxevents - 告知内核有多少个 events
// timeout - 超时时间，单位为毫秒
// 成功返回 需要处理的事件数目，失败返回 -1，超时返回 0
int epoll_wait(int epfd, struct epoll_event *event, int maxevents, int timeout);
```


**边缘触发和水平触发模式**：

水平触发（Level Trigger，LT）：只要读缓冲区不为空，写缓冲区不满，那么`epoll_wait()`就会一直返回就绪。

边缘触发（Edge Trigger，ET）：缓冲区的数据有变化，`epoll_wait()`就会返回就绪。使用 ET 模式，必须保证要**一次性读完数据和写完数据**。







## 2. 简易多人聊天室 v1.0




### 2.1 代码实现


```c
// multiChat01.c

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT "9034"

void *get_in_addr(struct sockaddr* sa)
{
        if (sa->sa_family == AF_INET)
        {
                return &(((struct sockaddr_in*)sa)->sin_addr);
        }
        return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
        fd_set master; // 主要的文件描述符set
        fd_set read_fds; // 暂存fd set

        struct addrinfo hints, *ai, *p;
        struct sockaddr_storage remoteaddr; // client addr

        int yes = 1;
        int rv;
        int listener;
        int fdmax;
        int newfd;
        int i, j;
        socklen_t addrlen;

        char buf[4096]; // 存储 client 数据的缓冲区
        int nbytes;

        char remoteIP[INET6_ADDRSTRLEN];

        int clients = 0;
        time_t idle_start;
        struct timeval tv;
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;

        // getaddrinfo
        if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0)
        {
                fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
                exit(1);
        }

        // 遍历 ai 中获取的地址信息
        for (p = ai; p != NULL; p = p->ai_next)
        {
                // socket
                if ((listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
                {
                        continue;
                }

                // 避开错误信息 "address already in use"
                setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

                // bind
                if (bind(listener, p->ai_addr, p->ai_addrlen) < 0)
                {
                        close(listener); // 避免文件描述符泄露
                        continue;
                }

                break;
        }

        if (p == NULL)
        {
                fprintf(stderr, "selectserver: failed to bind\n");
                exit(2);
        }

        freeaddrinfo(ai);  // 释放链表

        // listen
        if (listen(listener, 10) == -1)
        {
                perror("listen");
                exit(3);
        }

        // 将 listener 新增到 master set
        FD_SET(listener, &master);

        // 持续追踪最大的 fd
        fdmax = listener;

        idle_start = time(NULL);

        // 主要循环
        for( ; ; )
        {
                read_fds = master;
                tv.tv_sec = 1;
                tv.tv_usec = 0;
                if (select(fdmax + 1, &read_fds, NULL, NULL, &tv) == -1)
                {
                        perror("select");
                        exit(4);
                }

                // 定时器：无客户端连接超过60秒则关闭服务器
                if (clients == 0 && time(NULL) - idle_start >= 60)
                {
                        printf("selectserver：空闲超时，服务器关闭\n");
                        break;
                }
                // 在现存的连接中寻找需要读取的数据
                for (i = 0; i <= fdmax; ++i)
                {
                        if (FD_ISSET(i, &read_fds))
                        {
                                if (i == listener)
                                {
                                        // 有新连接进入
                                        addrlen = sizeof(remoteaddr);
                                        // accept
                                        newfd = accept(listener, (struct sockaddr *)&remoteaddr, &addrlen);

                                        if (newfd == -1)
                                        {
                                                perror("accept");
                                        }
                                        else
                                        {
                                                FD_SET(newfd, &master);
                                                if (newfd > fdmax)
                                                {
                                                        fdmax = newfd;
                                                }
                                                printf("selectserver：新连接来自 %s，套接字 %d 已进入聊天室\n",
                                                                inet_ntop(remoteaddr.ss_family, get_in_addr((struct sockaddr*)&remoteaddr),
                                                                        remoteIP, INET6_ADDRSTRLEN), newfd);
                                                clients++;
                                        }
                                }
                                else
                                {
                                        // 处理来自 client 的数据
                                        if ((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0)
                                        {
                                                // 连接关闭
                                                if (nbytes == 0)
                                                {
                                                        printf("selectserver：套接字 %d 已退出聊天室\n", i);
                                                }
                                                else
                                                {
                                                        perror("recv");
                                                }
                                                close(i);
                                                FD_CLR(i, &master); // 从 master set 中移出
                                                clients--;
                                                if (clients == 0)
                                                        idle_start = time(NULL);
                                        }
                                        else
                                        {
                                                buf[strcspn(buf, "\r\n")] = 0;
                                                if (strcmp(buf, "quit") == 0)
                                                {
                                                        printf("selectserver：套接字 %d 已退出聊天室\n", i);
                                                        close(i);
                                                        FD_CLR(i, &master);
                                                        clients--;
                                                        if (clients == 0)
                                                                idle_start = time(NULL);
                                                        nbytes = sprintf(buf, "套接字 %d 已退出聊天室\n", i);
                                                }
                                                for (j = 0; j <= fdmax; ++j)
                                                {
                                                        if (FD_ISSET(j, &master))
                                                        {
                                                                if (j != listener && j != i)
                                                                {
                                                                        if (send(j, buf, nbytes, 0) == -1)
                                                                        {
                                                                                perror("send");
                                                                        }
                                                                }
                                                        }
                                                }
                                        }
                                }
                        }
                }
        }

        return 0;
}

```


### 2.2 编译运行

```bash
# 编译
gcc -o multiChat_demo multiChat.c
```

在同一台终端实验：

```bash
# 运行
./multiChat_demo

# 开启其他窗口（至少两个，因为发送的消息并不在服务器端显示）
#      hostname   port
telnet 127.0.0.1 9034


# 退出
quit
```




## 3. 多人聊天室 v2.0

使用`epoll()`替换`select()`，实现高并发连接。


### 3.1 代码实现

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <errno.h>

#define PORT "9034"
#define MAX_EVENTS 4096 // 最大时间数 
#define MAX_CLIENTS 4096

void *get_in_addr(struct sockaddr* sa)
{
        if (sa->sa_family == AF_INET)
        {
                return &(((struct sockaddr_in*)sa)->sin_addr);
        }
        return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

static void set_nonblocking(int fd)
{
        int flags = fcntl(fd, F_GETFL, 0);
        fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

// 从 client_fds 数组中移除指定 fd
static void remove_client(int fd, int *client_fds, int *count)
{
        for (int k = 0; k < *count; k++)
        {
                if (client_fds[k] == fd)
                {
                        client_fds[k] = client_fds[--(*count)]; // 用尾元素替换，count 递减
                        return;
                }
        }
}

// 检查 fd 是否在 client_fds 中（防止同批次事件中已关闭的 fd 被重复处理）
static int client_exists(int fd, int *client_fds, int count)
{
        for (int k = 0; k < count; k++)
                if (client_fds[k] == fd)
                        return 1;
        return 0;
}


int main(void)
{
        int client_fds[MAX_CLIENTS]; // 客户端 fd 数组，替代 fd_set
        int client_count = 0;

        struct addrinfo hints, *ai, *p;
        struct sockaddr_storage remoteaddr; // client addr

        int yes = 1;
        int rv;
        int listener;
        int newfd;
        int i, j;
        socklen_t addrlen;

        char buf[4096]; // 存储 client 数据的缓冲区
        int nbytes;

        char remoteIP[INET6_ADDRSTRLEN];

        time_t idle_start;

        int epfd;
        struct epoll_event ev, events[MAX_EVENTS];

        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;

        // getaddrinfo
        if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0)
        {
                fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
                exit(1);
        }

        // 遍历 ai 中获取的地址信息
        for (p = ai; p != NULL; p = p->ai_next)
        {
                // socket
                if ((listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
                {
                        continue;
                }

                // 避开错误信息 "address already in use"
                setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

                // bind
                if (bind(listener, p->ai_addr, p->ai_addrlen) < 0)
                {
                        close(listener); // 避免文件描述符泄露
                        continue;
                }

                break;
        }


        if (p == NULL)
        {
                fprintf(stderr, "selectserver: failed to bind\n");
                exit(2);
        }

        freeaddrinfo(ai);  // 释放链表

        // listen
        if (listen(listener, SOMAXCONN) == -1)
        {
                perror("listen");
                exit(3);
        }

        set_nonblocking(listener);

        idle_start = time(NULL);

        // epoll 初始化
        epfd = epoll_create1(0);
        ev.events = EPOLLIN;
        ev.data.fd = listener;
        epoll_ctl(epfd, EPOLL_CTL_ADD, listener, &ev);

        // 主要循环
        for( ; ; )
        {
                int nfds = epoll_wait(epfd, events, MAX_EVENTS, 1000);
                if (nfds == -1)
                {
                        perror("epoll_wait");
                        exit(4);
                }

                // 定时器：无客户端连接超过60秒则关闭服务器
                if (client_count == 0 && time(NULL) - idle_start >= 60)
                {
                        printf("selectserver：空闲超时，服务器关闭\n");
                        break;
                }

                // 在现存的活动连接中处理事件
                for (i = 0; i < nfds; ++i)
                {
                        if (events[i].data.fd == listener)
                        {
                                // 有新连接进入（循环 accept 以应对高并发连接风暴）
                                while (1)
                                {
                                        addrlen = sizeof(remoteaddr);
                                        newfd = accept(listener, (struct sockaddr *)&remoteaddr, &addrlen);

                                        if (newfd == -1)
                                        {
                                                if (errno == EAGAIN || errno == EWOULDBLOCK)
                                                        break;
                                                perror("accept");
                                                break;
                                        }

                                        set_nonblocking(newfd);
                                        if (client_count >= MAX_CLIENTS)
                                        {
                                                printf("selectserver：连接数已达上限 %d，拒绝新连接\n", MAX_CLIENTS);
                                                close(newfd);
                                                break;
                                        }
                                        client_fds[client_count++] = newfd;
                                        ev.events = EPOLLIN;
                                        ev.data.fd = newfd;
                                        epoll_ctl(epfd, EPOLL_CTL_ADD, newfd, &ev);
                                        printf("selectserver：新连接来自 %s，套接字 %d 已进入聊天室\n",
                                                        inet_ntop(remoteaddr.ss_family, get_in_addr((struct sockaddr*)&remoteaddr),
                                                                remoteIP, INET6_ADDRSTRLEN), newfd);
                                }
                        }
                        else
                        {
                                int client_fd = events[i].data.fd;

                                // 同一批次事件中可能已被前序事件关闭（fd 重用），跳过
                                if (!client_exists(client_fd, client_fds, client_count))
                                        continue;

                                // 处理来自 client 的数据
                                if ((nbytes = recv(client_fd, buf, sizeof(buf), 0)) <= 0)
                                {
                                        // 连接关闭
                                        if (nbytes == 0)
                                        {
                                                printf("selectserver：套接字 %d 已退出聊天室\n", client_fd);
                                        }
                                        else
                                        {
                                                perror("recv");
                                        }
                                        epoll_ctl(epfd, EPOLL_CTL_DEL, client_fd, NULL);
                                        close(client_fd);
                                        remove_client(client_fd, client_fds, &client_count);
                                        if (client_count == 0)
                                                idle_start = time(NULL);
                                }
                                else
                                {
                                        buf[strcspn(buf, "\r\n")] = 0;
                                        if (strcmp(buf, "quit") == 0)
                                        {
                                                printf("selectserver：套接字 %d 已退出聊天室\n", client_fd);
                                                epoll_ctl(epfd, EPOLL_CTL_DEL, client_fd, NULL);
                                                close(client_fd);
                                                remove_client(client_fd, client_fds, &client_count);
                                                if (client_count == 0)
                                                        idle_start = time(NULL);
                                                nbytes = sprintf(buf, "套接字 %d 已退出聊天室\n", client_fd);
                                        }
                                        for (j = 0; j < client_count; ++j)
                                        {
                                                int target = client_fds[j];
                                                if (target != client_fd)
                                                {
                                                        int total = 0;
                                                        int retry = 0;
                                                        while (total < nbytes)
                                                        {
                                                                int sent = send(target, buf + total, nbytes - total, 0);
                                                                if (sent == -1)
                                                                {
                                                                        if ((errno == EAGAIN || errno == EWOULDBLOCK) && retry < 3)
                                                                {
                                                                        retry++;
                                                                        usleep(100);
                                                                        continue;
                                                                }
                                                                        if (errno != EPIPE)
                                                                                perror("send");
                                                                        break;
                                                                }
                                                                total += sent;
                                                                retry = 0;
                                                        }
                                                }
                                        }
                                }
                        }
                }
        }

        return 0;
}

```


### 3.2 编译运行


### 3.3 测试代码


### 3.4 连接测试

```bash
# 将服务器的输出重定向到 日志文件中
./multiChat02 > /tmp/server4k2.log 2>&1 & sleep 0.5

# 测试 4000 个连接接入
./bench_client 4000 200 10 2>&1 | grep -E "^(===|---|成功|发送|收到|目标|测试|  进度)" 

kill %1 2>/dev/null; wait 2>/dev/null

# 查看返回状态
echo "exit=$?"
echo "---"
tail -3 /tmp/server4k2.log
```