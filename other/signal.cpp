#include <iostream>
#include <csignal>
#include <unistd.h> // for sleep()

/*
   信号是由操作系统传给进程的中断，会提早终止一个程序

   信号处理的本质在于 允许程序响应异步事件
*/


// 示例1. signal

// 信号处理函数
void signalHandler(int signum)
{
	std::cout << "Caught signal " << signum << ", terminating graceful..." << "\n";
	// do something...
	exit(signum); //退出程序
}

int main()
{
	// 注册信号处理程序
	signal(SIGINT, signalHandler);

	std::cout << "Press ctrl+c to trigger the signal handler..." << "\n";

	while (true)
	{
		std::cout << "Running..." << "\n";
		sleep(1);
	}

	return 0;
}

// 示例2. sigaction()
// sigaction()提供丰富的功能，允许设置信号处理的行为，如恢复默认处理和设置信号屏蔽字

// 信号处理函数 
void signalHandler2(int signum, siginfo_t *info, void *context)
{
	std::cout << "Caught signal " << signum << ", terminating gracefully..." << "\n";
	exit(signum);
}

int main()
{
	struct sigaction action;
	memset(&action, 0, sizeof(action));
	action.sa_sigaction = signalHandler;
	action.sa_flags = SA_SIGINFO;

	if (sigaction(SIGINT, &action, nullptr) == - 1)
	{
		std::cerr << "Error registering signal handler" << "\n";
		return 1;
	}

	std::cout << "Press ctrl+c to trigger the signal handler..." << "\n";

	while (true)
	{
		std::cout << "Running..." << "\n";
		sleep(1);
	}

	return 0;
}

