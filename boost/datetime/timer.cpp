#include <iostream>
#include <boost/timer.hpp>

int main()
{
	boost::timer t; // 声明一个计时器对象，开始计时
	
	// 可度量的最大时间，以小时为单位
	std::cout << "max timespan: " << t.elapsed_max() / 3600 << "h" << std::endl;
	
	// 可度量的最小时间，以秒为单位
	std::cout << "min timespan: " << t.elapsed_min() << "s" << std::endl;

	// 输出已经流逝的时间
	std::cout << "now time elapsed: " << t.elapsed() << "s" << std::endl;

	return 0;
}
