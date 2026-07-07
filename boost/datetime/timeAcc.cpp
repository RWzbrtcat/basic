#include <iostream>
#define BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG
#include <boost/date_time/posix_time/posix_time.hpp>


int main()
{
	boost::posix_time::time_duration td1(1, 20, 30, 4000);

	std::cout << "fractional_seconds(): " << td1.fractional_seconds() << std::endl;


	// unit 返回一个 time_duration 对象，是 time_duration 计量的最小单位
	// 默认情况下是微秒，定义了宏的话，则为纳秒
	boost::posix_time::time_duration td2 = td1.unit();
	std::cout << "unit: " << to_iso_string(td2) << std::endl;

	// 检测当前的时间精确度
	std::cout << "resolution: " << td1.resolution() << std::endl;
	std::cout << "秒的位数: " << td1.num_fractional_digits() << std::endl;
	return 0;
}

