#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // pipe() 所在头文件
#include <sys/wait.h>

int main()
{
	int fd[2]; // fd[0] 读 fd[1] 写
	
	// 成功返回0，否则返回-1
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	
	// 必须在fork()中调用pipe()，否则子进程不会继承文件描述符
	// 两个进程不共享祖先进程，就不能使用pipe
	pid_t pid = fork();

	if (pid == 0)
	{
		// 子进程 - 读
		close(fd[1]);
		char buf[128];
		ssize_t n = read(fd[0], buf, sizeof(buf) - 1);
		if (n > 0)
		{
			buf[n] = '\0';
			printf("child process receives: %s", buf);
		}
		close(fd[0]);
		exit(0);
	}
	else
	{
		// 父进程 - 写
		close(fd[0]);
		const char *msg = "pipe message!\n";
		printf("parent process sends: %s", msg);
		write(fd[1], msg, strlen(msg));
		close(fd[1]);
		wait(NULL);  // 等子进程结束
	}

	return 0;
}
