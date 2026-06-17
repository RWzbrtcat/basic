#define _GNU_SOURCE   #启用 GNU 扩展特性 必须在源文件最顶部，
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <mqueue.h>

#define MQ_NAME "/demo_mqueue"  // 必须以斜杠开头，后面可以包含一个或多个非斜杠字符
#define MAX_MSG 10
#define MSG_SIZE 256

// POSIX 消息队列 - 带类型和优先级的结构化异步消息

int main()
{
	struct mq_attr attr = {
		.mq_flags = 0, // 0 - 阻塞模式
		.mq_maxmsg = MAX_MSG, // 最大消息数
		.mq_msgsize = MSG_SIZE, // 每条消息最大字节数
		.mq_curmsgs = 0, // 当前队列中的消息数
	};
	
	// 失败返回-1
	mqd_t mq = mq_open(MQ_NAME, O_CREAT | O_RDWR, 0666, &attr);

	if (mq == (mqd_t)-1)
	{
		perror("mq_open");
		exit(1);
	}

	pid_t pid = fork();

	if (pid == 0)
	{
		// child process
		sleep(2);
		char buf[MSG_SIZE];
		unsigned int prio;

		printf("[childe process] waiting messages...\n");
		
		// &prio 存储消息优先级的变量指针
		while (1)
		{
			ssize_t n = mq_receive(mq, buf, MSG_SIZE, &prio);
			if (n == -1)
			{
				perror("mq_recieve");
				break;
			}
			if (strncmp(buf, "quit", 4) == 0)
			{
				break;
			}
			buf[n] = '\0';
			printf("[child process] receives (priority = %u): %s", prio, buf);

		}
		exit(0);
	}
	else
	{
		// parent process
		// 发送多条信息，不同优先级

		// 优先级越高越先被收到
		// 15 - 要发送的字节数
		// 5 - 消息优先级（0-31， 数字越大优先级越高）
		char *msg1 = "normal message: hello\n";
		char *msg2 = "emergency message: system alarm\n";
		char *msg3 = "normal message: world\n";
		char *msg4 = "quit\n";
		mq_send(mq, msg1, strlen(msg1), 5);
		// printf("msg1 len is %u", strlen(msg1));
		mq_send(mq, msg2, strlen(msg2), 31);
		// printf("msg2 len is %u", strlen(msg2));
		mq_send(mq, msg3, strlen(msg3), 1);
		// printf("msg3 len is %u", strlen(msg3));
		mq_send(mq, msg4, strlen(msg4), 0);

		printf("[parent process] sends three messages\n");
		wait(NULL);
	}

	mq_close(mq);
	mq_unlink(MQ_NAME);
	return 0;
}
