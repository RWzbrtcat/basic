#include "threadPool01.h"
#include <cstdio>
#include <stdlib.h>
#include <unistd.h>


class CMyTask : public CTask
{
public:
	CMyTask() = default;
	int Run()
	{
		printf("%s\n", (char*)m_ptrData);
		int x = rand() % 4 + 1;
		sleep(x);
		return 0;
	}
	~CMyTask() {}
};

int main()
{
	CMyTask taskObj;
	char szTmp[] = "hello!";
	taskObj.setData((void*)szTmp);
	CThreadPool threadpool(5);

	for (int i = 0; i < 10; ++i)
	{
		threadpool.AddTask(&taskObj);
	}

	while (1)
	{
		printf("有 %d 个任务需要处理!\n", threadpool.getTaskSize());
		//
		if (threadpool.getTaskSize() == 0)
		{
			if (threadpool.StopAll() == -1)
			{
				printf("清理线程池并退出!\n");
				exit(0);
			}

		}
		sleep(2);
	}
	return 0;
}
