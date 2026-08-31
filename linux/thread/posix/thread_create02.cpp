#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// 传递字符串参数
void *thread_func(void *arg)
{
	char *str;
	str = (char *)arg;
	printf("str = %s\n", str);

	return (void *)0;
}

int main(int argc, char *argv [])
{
	pthread_t pid;
	int ret;
	const char *str = "hello world!";
	
	// str 需转换为 void * 类型
	ret = pthread_create(&pid, NULL, thread_func, (void *)str);
	if (ret)
	{
		printf("pthread_create error!\n");
		return -1;
	}
	
	// 等待子线程结束
	ret = pthread_join(pid, NULL);
	if (ret)
	{
		printf("pthred_join error!\n");
		return -1;
	}

	return 0;
}
