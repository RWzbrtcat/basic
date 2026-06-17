#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/wait.h>

#define SOCK_PATH "/tmp/demp_socket"


int main()
{
	unlink(SOCK_PATH);

	// 创建 socket
	int server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (server_fd == -1)
	{
		perror("socket");
		exit(1);
	}

	// 绑定地址
	struct sockaddr_un addr;
	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);

	if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
	{
		perror("bind");
		exit(1);
	}
	if (listen(server_fd, 1) == -1)
	{
		perror("listen");
		exit(1);
	}

	pid_t pid = fork();

	if (pid == 0)
	{
		// child process - client
		int client_fd = socket(AF_UNIX, SOCK_STREAM, 0);
		if (connect(client_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		{
			perror("connect");
			exit(1);
		}

		// 发送两条消息
		const char *msgs[] = {
			"hello, this is Unix Socket message 1!\n",
			"this is message 2!\n"	
		};

		for (int i = 0; i < 2; ++i)
		{
			printf("[client] sends: %s", msgs[i]);
			write(client_fd, msgs[i], strlen(msgs[i]));
			sleep(1);
		}
		close(client_fd);
		exit(0);
	}
	else
	{
		// parent process: server
		int conn_fd = accept(server_fd, NULL, NULL);
		if (conn_fd == -1)
		{
			perror("accept");
			exit(1);
		}

		// 读取消息
		char buf[256];
		for (int i = 0; i < 2; ++i)
		{
			ssize_t n = read(conn_fd, buf, sizeof(buf) - 1);
			if (n > 0)
			{
				buf[n] = '\0';
				printf("[server] receives: %s", buf);
			}
		}

		close(conn_fd);
		close(server_fd);
		wait(NULL);
		unlink(SOCK_PATH);
	}

	return 0;
}
