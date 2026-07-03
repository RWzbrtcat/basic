#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

int main()
{
	int year, month, day; // 输入出生年月份
	std::cin >> year >> month >> day;

	boost::gregorian::date d(year + 18, month, day);

	// 输出 18 岁生日时星期
	std::cout << "18 岁生日时星期: " << d.day_of_week() << std::endl;

	// 输出当月天数
	std::cout << "当月天数: " << d.end_of_month().day() << std::endl;

	// 输出当年天数
	int count = 0;
	// 累加每月天数
	boost::gregorian::month_iterator m_iter(boost::gregorian::date(year + 18, 1, 1));
	for (; m_iter < boost::gregorian::date(year + 19, 1, 1); ++m_iter)
	{
		count += m_iter->end_of_month().day();
	}

	std::cout << "当年天数: " << count << std::endl;

	return 0;
}
