#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

int main()
{
	boost::gregorian::date d(2002, 10, 2);
	boost::gregorian::day_iterator di(d); // 默认步长为 1 天
	++di;
	std::cout << "day: " << di->day() << std::endl;


	boost::gregorian::year_iterator yi(d, 10); // 步长为 10 年
	++yi;
	std::cout << "year: " << yi->year() << std::endl;
	return 0;
}
