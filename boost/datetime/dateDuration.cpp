#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>


int main()
{
	boost::gregorian::days dd1(10), dd2(-20), dd3(30);

	// date_duration 支持比较操作
	std::cout << (dd1 > dd2) << std::endl;
	std::cout << ((dd1 - dd3) == dd2) << std::endl;
	
	// 此外，date_time 库也提供 months years 和 weeks三个时长类
	boost::gregorian::weeks w(4); // 4 个星期
	std::cout << "4 个星期有: " << w.days() << " 天" << std::endl;
	
	boost::gregorian::months m1(5); // 5 个月
	boost::gregorian::years y1(2); // 2 年
	// months 和 years 支持 加减乘除 运算
	boost::gregorian::months m2 = y1 - m1;
	std::cout << "m1 和 y1 相差: " << m2.number_of_months() << " 月" << std::endl;
	boost::gregorian::months m3 = y1 + m1;
	std::cout << "m1 和 y1 总和: " << m3.number_of_months() << " 月" << std::endl;

	return 0;
}
