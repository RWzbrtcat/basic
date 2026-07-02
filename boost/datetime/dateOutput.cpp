#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

int main()
{
	boost::gregorian::date d1(2025, 5, 5);
	// 转换为 YYYY-mmm-DD 格式的字符串
	std::cout << boost::gregorian::to_simple_string(d1) << std::endl;
	
	// 转换为 YYYYMMDD 格式的字符串
	std::cout << boost::gregorian::to_iso_string(d1) << std::endl;

	// 转换为 YYYY-mm-DD 格式的字符串
	std::cout << boost::gregorian::to_iso_extended_string(d1) << std::endl;

	return 0;
}
