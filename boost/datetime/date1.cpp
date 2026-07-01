#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
// using namespace boost::gregorian

int main()
{	
	boost::gregorian::date d1; // 无效的日期
	
	boost::gregorian::date d2(2024, 1, 1);  // 使用数字构造日期
	std::cout << "d2: " << d2 << std::endl;
	
	boost::gregorian::date d3(2025, boost::gregorian::May, 1); // 使用英文指定月份
	std::cout << "d3: " << d3 << std::endl;

	boost::gregorian::date d4(d3); // 支持拷贝构造
	std::cout << "d4: " << d4 << std::endl;

	// 可从字符串加载日期
	std::cout << "--------从字符串加载日期---------" << std::endl;
	boost::gregorian::date d5 = boost::gregorian::from_string("2001-03-04");
	std::cout << "d5: " << d5 << std::endl;
	
	boost::gregorian::date d6(boost::gregorian::from_string("2002/5/6"));
	std::cout << "d6: " << d6 << std::endl;

	boost::gregorian::date d7 = boost::gregorian::from_undelimited_string("20030708");
	std::cout << "d7: " << d7 << std::endl;

	std::cout << "------------day_clock------------" << std::endl;
	// day_clock 天级别时钟
	// 返回当天的日期对象 - 本地日期
	std::cout << boost::gregorian::day_clock::local_day() << std::endl;
	// UTC 日期
	std::cout << boost::gregorian::day_clock::universal_day() << std::endl;

	return 0;
}
