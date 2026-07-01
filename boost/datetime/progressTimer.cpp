#include <iostream>
#include <sstream>
#include <boost/progress.hpp>


int main()
{
	{
		boost::progress_timer t;
	}
	// 在退出作用域或者程序结束会自动输出流逝的时间
	
	// 将析构时的输出定向到 stringstream 中
	std::stringstream ss;
	{
		boost::progress_timer t(ss);
	}
	std::cout << ss.str();

	return 0;
}
