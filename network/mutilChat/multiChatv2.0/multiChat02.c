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
#define MAX_EVENTS 4096
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
	int i, j, v;
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
