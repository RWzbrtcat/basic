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

	std::cout << "-----------创建特殊日期-----------" << std::endl;
	boost::gregorian::date d8(boost::gregorian::neg_infin); // 负无限日期
	std::cout << "负无限日期: " << d8 << std::endl;
	boost::gregorian::date d9(boost::gregorian::pos_infin); // 正无限日期
	std::cout << "正无限日期: " << d9 << std::endl;
	boost::gregorian::date d10(boost::gregorian::not_a_date_time); // 无效日期
	std::cout << "无效日期: " << d10 << std::endl;
	boost::gregorian::date d11(boost::gregorian::max_date_time); // 最大可能日期
	std::cout << "最大可能日期: " << d11 << std::endl;
	boost::gregorian::date d12(boost::gregorian::min_date_time); // 最小可能日期
	std::cout << "最小可能日期: " << d12 << std::endl;

	return 0;
}
