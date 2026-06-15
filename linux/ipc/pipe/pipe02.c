
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

// 动态交互


int main()
{
	int fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(1);
	}

	pid_t pid = fork();

	if (pid == 0)
	{
		close(fd[1]);
		char buf[128];
		ssize_t n;
		while ((n = read(fd[0], buf, sizeof(buf) - 1)) > 0)
		{
			buf[n] = '\0';
			printf("child process recieves: %s", buf);
		}
		printf("child process pipe has closed, exit!\n");
		close(fd[0]);
		exit(0);
	}
	else
	{
		close(fd[0]);
		char input[128];
		printf("parent inputs message(quit is exit): \n");
		while (1)
		{
			printf("> ");
			fflush(stdout); // 
			if (fgets(input, sizeof(input), stdin) == NULL){
				break;
			}
			// exit condition
			if (strncmp(input, "quit", 4) == 0)
			{
				break;
			}

			write(fd[1], input, strlen(input));

		}
		close(fd[1]);
		wait(NULL);
		printf("parent process ends!\n");
	}

	return 0;
}
