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
	int i, j, v;
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





