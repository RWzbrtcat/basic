#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>


int main()
{
	boost::gregorian::date d1(2025, 10, 1);

	std::cout << "年: " << d1.year() << std::endl;
	std::cout << "月: " << d1.month() << std::endl;
	std::cout << "日: " << d1.day() << std::endl;
	// 一次性获取全部日期
	boost::gregorian::date::ymd_type ymd = d1.year_month_day();
	std::cout << "年: " << ymd.year << " 月: " << ymd.month << " 日: " << ymd.day << std::endl;

	// 返回 date 的星期数，0 表示星期天
	std::cout << "星期: " << d1.day_of_week() << std::endl;

	// 返回 date 是当年的第几天
	std::cout << "今年第 " << d1.day_of_year() << " 天" << std::endl;

	// 返回 date 所在周是当年的第几周
	std::cout << "今年第 " << d1.week_number() << " 周" << std::endl;

	return 0;
}

