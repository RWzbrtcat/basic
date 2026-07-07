#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{
	boost::gregorian::date d(2000, 1, 1);
	boost::posix_time::time_duration td(2, 30, 10);

	boost::posix_time::ptime p(d, td);
	std::cout << "p.date: " << p.date() << std::endl;
	std::cout << "p.time: " << p.time_of_day() << std::endl;

	// 字符串输出
	std::cout << to_simple_string(p) << std::endl;
	std::cout << to_iso_string(p) << std::endl;
	std::cout << to_iso_extended_string(p) << std::endl;

	return 0;
}
