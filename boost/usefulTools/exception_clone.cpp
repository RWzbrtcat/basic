#include <iostream>
#include <boost/throw_exception.hpp>
#include <boost/exception/all.hpp>

// 线程工作函数
void thread_work()
{
	boost::throw_exception(std::logic_error("test"));
}

int main()
{
	try
	{
		thread_work(); // 启动一个线程，可能抛出异常
	}
	catch (...)
	{
		boost::exception_ptr e = boost::current_exception();
		std::cout << boost::current_exception_diagnostic_information() << std::endl;
	}

	return 0;
}
