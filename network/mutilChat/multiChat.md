# 获取本地地址


### 获取localhost的ip地址

- [虚拟机]只能获取lo口的地址？

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#define PORT "10002"


void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
    struct addrinfo hints, *ai, *p;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    int rv;

    char ipstr[INET6_ADDRSTRLEN];

    // or localhost -> hostname
    // char hostname[256];
    // gethostname(hostname, sizeof(hostname));
    // printf("hostname: %s\n", hostname);

    if ((rv = getaddrinfo("localhost", PORT, &hints, &ai)) != 0)
    {
        fprintf(stderr, "ip addr print: %s\n", gai_strerror(rv));
        exit(1);
    }

    for (p = ai; p != NULL; p = p->ai_next)
    {
        inet_ntop(p->ai_family, get_in_addr(p->ai_addr), ipstr, sizeof(ipstr));
        printf("ipaddr: %s\n", ipstr);
    }
    freeaddrinfo(ai);
    return 0;
}


```


### 使用getifaddrs()

- 可以获取所有网口的IP地址

```c

#include <stdio.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <net/if.h>

int main() {
    struct ifaddrs *ifaddr, *ifa;
    char ipstr[INET6_ADDRSTRLEN];
    int count = 0;
    
    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        return 1;
    }
    
    printf("系统所有网络接口:\n");
    printf("%-10s %-8s %-20s %s\n", 
           "接口名", "协议", "IP地址", "状态");
    printf("----------------------------------------\n");
    
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL) continue;
        
        int family = ifa->ifa_addr->sa_family;
        
        if (family == AF_INET || family == AF_INET6) {
            count++;
            
            void *addr;
            if (family == AF_INET) {
                addr = &((struct sockaddr_in*)ifa->ifa_addr)->sin_addr;
            } else {
                addr = &((struct sockaddr_in6*)ifa->ifa_addr)->sin6_addr;
            }
            
            inet_ntop(family, addr, ipstr, sizeof(ipstr));
            
            printf("%-10s %-8s %-20s %s\n",
                   ifa->ifa_name,
                   family == AF_INET ? "IPv4" : "IPv6",
                   ipstr,
                   (ifa->ifa_flags & IFF_UP) ? "UP" : "DOWN");
        }
    }
    
    printf("----------------------------------------\n");
    printf("总共找到 %d 个网络接口地址\n", count);
    
    freeifaddrs(ifaddr);
    return 0;
}

```



## 多人对话



- 进一步需处理的问题

支持中文输入

不限制用户输入

无客户端连接(1min)后自动退出



```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT "9034"
#define BUFSIZE 256

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
    fd_set master; // 保存所有活跃的socket(监听socket + 客户端socket)
    fd_set read_fds;
    int fdmax; // 最大 file descriptor数目

    int listener; // listening socket descriptor
    int newfd; // accpet() socket descriptor
    struct sockaddr_storage remoteaddr; // client addr;
    socklen_t addr_len;

    char buf[BUFSIZE]; // 存储 client 数据的缓冲区
    int nbytes;

    char remoteIP[INET6_ADDRSTRLEN];

    int yes = 1;
    int i, j, rv;

    struct addrinfo hints, *ai, *p;

    FD_ZERO(&master); // 清除 master 与 temp sets
    FD_ZERO(&read_fds);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if ((rv = getaddrinfo(NULL, PORT, &hints, &ai)) != 0)
    {
        fprintf(stderr, "selectserver:%s\n", gai_strerror(rv));
        exit(1);
    }

    for (p = ai; p != NULL; p = p->ai_next)
    {
        listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (listener < 0)
        {
            continue;
        }

        // 避免错误信息 "address already in use"
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0)
        {
            close(listener);
            continue;
        }
        break;
    }

    if (p == NULL)
    {
        fprintf(stderr, "selectserver: failed to bind\n");
        exit(2);
    }

    if (listen(listener, 10) == -1)
    {
        perror("listen");
        exit(3);
    }

    FD_SET(listener, &master);

    // 持续追踪最大的 file descriptor
    fdmax = listener;

    for( ; ; )
    {
        read_fds = master;
        // 返回后,read_fds中只保留(读)就绪的socket
        if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1)
        {
            perror("select");
            exit(4);
        }

        //在现存的连接中寻找需要读取的数据
        // 遍历查找就绪的socket
        for (i = 0; i <= fdmax; ++i)
        {
            if (FD_ISSET(i, &read_fds))
            {
                // 新连接到达
                if (i == listener)
                {
                    addr_len = sizeof(remoteaddr);
                    newfd = accept(listener, (struct sockaddr *)&remoteaddr, &addr_len);

                    if (newfd == -1)
                    {
                        perror("accept");
                    }
                    else
                    {
                        // 将新socket加入master集合
                        FD_SET(newfd, &master);
                        // 更新最大fd值
                        if (newfd > fdmax)
                        {
                            fdmax = newfd;
                        }
                        printf("selectserver: new connection from %s on socket %d\n",
                                   inet_ntop(remoteaddr.ss_family, get_in_addr((struct sockaddr*)&remoteaddr),
                                    remoteIP, INET6_ADDRSTRLEN), newfd);
                    }
                }
                else
                {
                    memset(buf, 0, sizeof(buf)); // 清除残留数据
                    // 处理来自client的数据
                    if ((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0)
                    {
                        if (nbytes == 0)
                        {
                            printf("selectserver: socket %d hund up\n", i);
                        }
                        else
                        {
                            perror("recv");
                        }
                        close(i);
                        FD_CLR(i, &master); // 从master set 中移除
                    }
                    else
                    {
                        // windows终端输入会带 "\r\n" 两个字符 
                        buf[strcspn(buf, "\r")] = 0; // buf[strcspn(buf, "\n")] = 0 linux 终端
                        /*
                        printf("buf length:%ld\n", strlen(buf));
                        // printf("buf content:%s\n", buf);
                        for (int k = 0; k < strlen(buf); k++)
                        {
                            if (buf[k] == ' ')
                            {
                                printf("_");
                            }
                            else
                            {
                                printf("%c", buf[k]);
                            }
                        }
                        printf("\n");
                        */
                        if (strcmp(buf, "quit") == 0 || strcmp(buf, "exit") == 0)
                        {
                            printf("selectserver: socket %d exit\n", i);
                            char msg[256];
                            memset(msg, 0, sizeof(msg));
                            sprintf(msg, "socket %d out\n", i);
                            for (j = 0; j <= fdmax; j++)
                            {
                                if (FD_ISSET(j, &master))
                                {
                                    if (j != i && j != listener)
                                    {
                                        if (send(j, msg, sizeof(msg), 0) == -1)
                                        {
                                            perror("quit send");
                                        }
                                    }
                                }
                            }
                            close(i);
                            FD_CLR(i, &master);
                        }

                        else
                        {
                            for (j = 0; j <= fdmax; j++)
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
    }

    return 0;
}

```





## 同步/异步 I/O 多工
