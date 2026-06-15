#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define FIFO_PATH "/home/knowledges/linux/ipc/fifo/fifo_file"


// FIFO - 命名管道
// 任意两个进程通过文件路径通信

int main()
{	
	// 删除可能残留的旧 FIFO
	unlink(FIFO_PATH);
	
	// mkfifo 用于在文件系统中创建一个命名管道（FIFO特殊文件）
	// FIFO_PATH - 要创建的 FIFO 文件的路径
	// 0666 - 文件权限
	// 成功返回0，失败返回-1
	if (mkfifo(FIFO_PATH, 0666) == -1)
	{
		perror("mkfifo");
		exit(1);
	}

	pid_t pid = fork();

	if (pid == 0)
	{
		// 子进程 读取
		int fd = open(FIFO_PATH, O_RDONLY);
		char buf[128];
		ssize_t n = read(fd, buf, sizeof(buf) - 1);
		if (n > 0)
		{
			buf[n] = '\0';
			printf("child process receive: %s", buf);
		}
		close(fd);
		exit(0);
	}
	else
	{
		// 父进程 写入
		int fd = open(FIFO_PATH, O_WRONLY);
		const char *msg = "fifo message!\n";
		printf("parent chile sends: %s", msg);
		write(fd, msg, strlen(msg));
		close(fd);
		wait(NULL); // 
	}

	unlink(FIFO_PATH); // 清理
	return 0;
}
