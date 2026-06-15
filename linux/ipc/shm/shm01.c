#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>

#define SHM_NAME "/demo_shm"
#define SHM_SIZE 4096

int main()
{
	// 创建共享内存对象
	int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
	if (fd == -1)
	{
		perror("shm_open!\n");
		exit(1);
	}

	// 设置大小
	if (ftruncate(fd, SHM_SIZE) == -1)
	{
		perror("ftruncate!\n");
		exit(1);
	}

	// 映射到进程地址空间
	char *shm = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (shm == MAP_FAILED)
	{
		perror("mmap!\n");
		exit(1);
	}
	close(fd);

	pid_t pid = fork();
	if (pid == 0)
	{
		// child process
		printf("[child process] waiting parent process wirting...\n");
		printf("[child process] recieves: %s", shm);
		exit(0);
	}
	else
	{
		// parent process
		const char *msg = "shared memory demo\n";
		printf("[parent process] sends: %s", msg);
		memcpy(shm, msg, strlen(msg) + 1); // 
		wait(NULL);
	}

	// 清理
	munmap(shm, SHM_SIZE);
	shm_unlink(SHM_NAME);
	return 0;
}
