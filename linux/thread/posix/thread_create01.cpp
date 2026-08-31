#include <stdio.h>
#include <pthread.h>
#include <unistd.h>  // for sleep

// 线程函数

void *thread_func(void *arg)
{
	printf("thread func...\n");
	return (void *)0;
}

int main(int argc, char *argv [])
{
	pthread_t pid;
	int ret;
	
	// 创建线程
	ret = pthread_create(&pid, NULL, thread_func, NULL);
	if (ret)
	{
		printf("pthread_create error!\n");
		return -1;
	}

	// sleep(1);// 用于等待子线程结束，可使用 pthread_join 替代
	ret = pthread_join(pid, NULL);
	if (ret)
	{
		printf("pthread_join error!\n");
		return -1;
	}

	printf("thread is created!\n");

	return 0;
}

