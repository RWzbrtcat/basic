#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

int main()
{
	boost::gregorian::date d1(2012, 2, 2), d2(2025, 8, 8);
	// 指定区间的两个端点构造区间
	boost::gregorian::date_period dp1(d1, d2);
	// 指定左端点 加 时长构造区间
	boost::gregorian::days dd(23);
	boost::gregorian::date_period dp2(d1, dd);

	// 返回区间的两个端点
	std::cout << "begin: " << dp1.begin() << std::endl;
	std::cout << "last: " << dp1.last() << std::endl;

	// 返回 last 后的第一天
	std::cout << "end: " << dp1.end() << std::endl;

	// 返回日期区间长度，以天为单位
	std::cout << "length: " << dp1.length() << std::endl;
	
	// 比较运算 - 只有在两个日期区间不相交时有效
	boost::gregorian::date_period dp3(d2, dd);
	std::cout << (dp3 > dp2 ) << std::endl; 

	return 0;
}
