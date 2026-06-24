#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#define PORT "3490"
#define BACKLOG 10


void sigchild_handler(int s)
{
	while(waitpid(-1, NULL, WNOHANG) > 0);
}

void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}



int main()
{
	// 定义变量和初始化值
	int sockfd, new_fd; // sockfd 是listen，newfd 是新的连接
	struct addrinfo hints, *p, *servinfo;
	struct sockaddr_storage their_addr; // 连接者的地址资料
	socklen_t sin_size;
	struct sigaction sa;
	int yes = 1;
	char s[INET6_ADDRSTRLEN];
	int rv;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	// getaddrinfo
	
	if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}
	
	// 循环找到可用的连接地址
	for (p = servinfo; p != NULL; p = p->ai_next)
	{
		// socket - 创建文件描述符
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
		{
			perror("server: socket");
			continue;
		}

		// 端口复用
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		{
			perror("setsockopt");
			exit(1);
		}

		// bind
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
		{
			close(sockfd); // 防止文件描述符泄露
			perror("bind");
			continue;
		}

		break;
	}
	
	if (p == NULL)
	{
		fprintf(stderr, "server: failed to bind\n");
		return 2;
	}
	
	// 释放结构体
	freeaddrinfo(servinfo);

	// listen - 监听该端口
	if (listen(sockfd, BACKLOG) == -1)
	{
		perror("listen");
		exit(1);
	}

	sa.sa_handler = sigchild_handler; // 处理全部死掉的 processes
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	if (sigaction(SIGCHLD, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(1);
	}

	printf("server: waiting for connections...\n");


	while (1)
	{
		sin_size = sizeof(their_addr);

		// accept
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);

		if (new_fd == -1)
		{
			perror("accept");
			continue;
		}

		inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof(s));

		printf("server: got connetion from %s\n", s);
		
		// 子进程返回 0，父进程返回新创建子进程的PID
		if (!fork())
		{
			close(sockfd); // child process 不需要 listen

			if (send(new_fd, "hello, world!", 13, 0) == -1)
			{
				perror("send");
			}
			close(new_fd);
			exit(0);

		}
		close(new_fd); // 父进程 不需要 new_fd
	}

	return 0;
}
