#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{
	// 初始化
	// 创建一个 5 小时 10 分钟 20 秒 3 毫秒的时间长度
	boost::posix_time::time_duration td1(5, 10, 20, 3000);
	
	// 可从工厂函数创建
	boost::posix_time::time_duration td2 = boost::posix_time::duration_from_string("6:20:30:004");

	// 访问 时 分 秒

	std::cout << "时: " << td1.hours() << std::endl;
	std::cout << "分: " << td1.minutes() << std::endl;
	std::cout << "秒: " << td1.seconds() << std::endl;

	std::cout << "时间长度总秒数: " << td1.total_seconds() << std::endl;
	std::cout << "时间长度总毫秒数: " << td1.total_milliseconds() << std::endl;
	std::cout << "时间长度总毫秒数: " << td1.total_microseconds() << std::endl;
	std::cout << "(long)总微秒数: " << td1.fractional_seconds() << std::endl;

	// 正负值
	boost::posix_time::hours h(-10);
	std::cout << "h是负值: " << h.is_negative() << std::endl;
	boost::posix_time::time_duration td3 = h.invert_sign();
	std::cout << "现在h的值为: " << td3.hours() << std::endl;

	// 字符串表示
	std::cout << to_simple_string(td1) << std::endl;
	std::cout << to_iso_string(td1) << std::endl;
		
	return 0;
}
