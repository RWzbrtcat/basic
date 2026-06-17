#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>

#define SEM_NAME "/demo_sem"
#define SHM_NAME "/demo_sem_shm"

// POSIX 命名信号量 - 进程间同步，保护共享资源

typedef struct{
	int counter;
} SharedData;


int main()
{
	// 创建信号量，初始值 = 1（互斥锁）
	sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
	if (sem == SEM_FAILED)
	{
		perror("sem_open");
		exit(1);
	}

	// 创建共享内存存放计数器
	int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
	// 
	ftruncate(fd, sizeof(SharedData));
	SharedData *shared = mmap(NULL, sizeof(SharedData), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	shared->counter = 0;
	close(fd);

	// 创建 3 个子进程同时递增计数器
	for (int i = 0; i < 3; ++i)
	{
		if (fork() == 0)
		{
			// 每个进程自增 100000 次
			for (int j = 0; j < 100000; ++j)
			{
				sem_wait(sem);    // P 操作 - 获取锁
				shared->counter++; // 临界区
				sem_post(sem);  // V 操作 - 释放锁
			}
			exit(0);
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		wait(NULL);
	}

	printf("3 个子进程各递增 100000 次\n");
	printf("计数器最终值 = %d \n", shared->counter);
	printf("%s\n", shared->counter == 300000 ? "信号量保护正确，无竞态条件" : "数据错误");

	// 清理
	sem_close(sem);
	sem_unlink(SEM_NAME);
	munmap(shared, sizeof(SharedData));
	shm_unlink(SHM_NAME);
	return 0;
}
