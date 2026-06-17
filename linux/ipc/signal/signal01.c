#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

// 信号 - 异步通知，适合进程控制和事件告警

// 信号处理函数
void handler(int sig, siginfo_t *info, void *ucontext)
{
	printf("[receive signal %d (%s)]\n", sig, strsignal(sig));
	if (info->si_pid != 0)
	{
		printf("sender pid = %d, data = %d\n", info->si_pid, info->si_value.sival_int);
	}
}

int main()
{
	// 信号处理器
	struct sigaction sa = {0};
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);

	sigaction(SIGUSR1, &sa, NULL); // 自定义信号1
	sigaction(SIGUSR2, &sa, NULL); // 自定义信号2
	sigaction(SIGTERM, &sa, NULL); // 终止信号

	printf("this process pid = %d\n\n", getpid());

	pid_t pid = fork();
	
	if (pid == 0)
	{
		printf("[child process %d] sends SIGUSR1 \n", getpid());
		union sigval val;
		val.sival_int = 42;
		sigqueue(getppid(), SIGUSR1, val); // 带数据发送

		sleep(1);

		printf("[child process %d] sends SUGUSR2 \n", getpid());
		kill(getppid(), SIGUSR2); // 普通发送

		sleep(1);

		printf("[child process %d] sends SIGTERM \n", getpid());
		kill(getppid(), SIGTERM); 

		exit(0);
	}
	else
	{
		printf("[parent process %d] waiting signals...\n", getpid());
		while (1)
		{
			pause(); // 挂起，等信号
		}
	}
	return 0;
}
