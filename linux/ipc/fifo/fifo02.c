#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_PATH "/home/knowledges/linux/ipc/fifo/fifo_file"

int main()
{
	unlink(FIFO_PATH);

	if (mkfifo(FIFO_PATH, 0666) == -1)
	{
		perror("mkfifo\n");
		exit(1);
	}

	pid_t pid = fork();

	if (pid == 0)
	{
		// child process
		int fd = open(FIFO_PATH, O_RDONLY);
		char buf[256];
		ssize_t n;
		while ((n = read(fd, buf, sizeof(buf) - 1)) > 0)
		{
			buf[n] = '\0';
			printf("child process recieves: %s", buf);
		}
		close(fd);
		exit(0);
	}
	else
	{
		// parent process
		int fd = open(FIFO_PATH, O_WRONLY);
		char input[256];
		printf("parent process inputs (quit exits): \n");
		while (1)
		{
			printf("> ");
			fflush(stdout); // 强制将缓冲区的数据立即输出到终端 
			if (fgets(input, sizeof(input), stdin) == NULL)
			{
				break;
			}
			if (strncmp(input, "quit", 4) == 0)
			{
				break;
			}
			write(fd, input, strlen(input));
		}
		close(fd);
		wait(NULL);
		printf("parent process ends\n");
	}

	unlink(FIFO_PATH);
	return 0;

}
