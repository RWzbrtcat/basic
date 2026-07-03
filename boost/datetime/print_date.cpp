#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>


int main()
{
	int year, month;
	std::cin >> year >> month; // 输入年份和月份
	boost::gregorian::date d(year, month, 1);

	// 打印日期
	for (boost::gregorian::day_iterator di(d); di != d.end_of_month(); ++di)
	{
		// 输出日期和星期
		std::cout << *di << " " << di->day_of_week() << std::endl;
	}
	return 0;
}
