#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

int main()
{
	boost::gregorian::date d1(2012, 1, 1);
	boost::gregorian::date d2(2025, 7, 7);
	
	std::cout << "d1 和 d2 相差: " << d2 - d1 << " 天" << std::endl;

	// 正常日期与特殊日期的运算结果都是特殊日期
	boost::gregorian::date d3(boost::gregorian::neg_infin);
	std::cout << "特殊日期运算结果: " << d3 - d2 << std::endl;



	return 0;
}
