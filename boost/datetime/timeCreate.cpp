#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{
	// 同时指定 date 和 time_duration 对象进行创建
	boost::gregorian::date d(2010, 10, 10);
	boost::posix_time::hours h(20);
	boost::posix_time::ptime p1(d, h);
	std::cout << "p1: " << p1 << std::endl;

	// 从字符串构造
	boost::posix_time::ptime p2 = boost::posix_time::time_from_string("2011-11-11 21:00:00");
	std::cout << "p2: " << p2 << std::endl;
	boost::posix_time::ptime p3 = boost::posix_time::from_iso_string("20121212T220000");
	std::cout << "p3: " << p3 << std::endl;

	// 获取当前时间
	boost::posix_time::ptime p4 = boost::posix_time::second_clock::local_time(); // 秒精确度
	std::cout << "p4: " << p4 << std::endl;
	boost::posix_time::ptime p5 = boost::posix_time::microsec_clock::universal_time(); // 微秒精确度
	std::cout << "p5: " << p5 << std::endl;
	

	return 0;
}
