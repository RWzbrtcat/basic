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


/*
   多人对话 - 待完善
   */


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
	fd_set master; // 保存所有活跃的 socket （监听socket + 客户端socket）
	fd_set read_fds;
	int fdmax; // 最大 file descriptor 数目

	int listener; 
	int newfd;
	struct sockaddr_storage remoteaddr; // client addr
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
		{fprintf(stderr, "selectserver:%s\n", gai_strerror(rv));
		exit(1);
	}

	for (p = ai; p!= NULL; p = p->ai_next)
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
		fprintf(stderr, "selectserver: faile to bind\n");
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

	for (; ;)
	{
		read_fds = master;
		// 返回后 read_fds中只保留（读）就绪的socket
		if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1)
		{
			perror("select");
			exit(4);
		}

		// 在现存的连接中寻找需要读取的数据
		// 遍历查找就绪的 socket
		for (i = 0; i <= fdmax; ++i)
		{
			if (FD_ISSET(i, &read_fds))
			{
				// 新连接到达
				if (i == listener)
				{
					addr_len = sizeof(remoteaddr);
					newfd = accept(listener, (struct sockaddr*)&remoteaddr, &addr_len);

					if (newfd == -1)
					{
						perror("accept");
					}
					else
					{
						// 将新 socket 加入master集合
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
					memset(buf, 0, sizeof(buf)); // 清楚残留数据
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
						FD_CLR(i, &master); // 从master set中移出
					}
					else
					{
						// windows终端输入会带 "\r\n" 两个字符
						buf[strcspn(buf, "\r")] = 0;

						if (strcmp(buf, "quit") == 0 || strcmp(buf, "exit") == 0)
						{
							printf("selectserver: socket %d exit\n", i);
							char msg[256];
							memset(msg, 0, sizeof(msg));
							sprintf(msg, "socket %d out\n", i);

							for (j = 0; j <= fdmax; ++j)
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
	}

	return 0;


}
