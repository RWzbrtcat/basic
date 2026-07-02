#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

int main()
{
	boost::gregorian::date d1(2025, 6, 6);
	
	// date 转换到 tm，将 tm 的时分秒均置为 0
	std::tm t = boost::gregorian::to_tm(d1);
	std::cout << "年: " << t.tm_year << " 月: " << t.tm_mon << " 日: " << t.tm_mday << std::endl;
	std::cout << "时分秒: " << t.tm_hour << t.tm_min << t.tm_sec << std::endl;

	// tm 转换到 date，只使用 年月日 三个成员
	boost::gregorian::date d2 = boost::gregorian::date_from_tm(t);
	std::cout << d2 << std::endl;
}
