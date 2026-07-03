#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

int main()
{
	boost::gregorian::date_period dp(boost::gregorian::date(2015, 5 ,5), boost::gregorian::days(20));
	
	std::cout << "begin: " << dp.begin() << " end: " << dp.end() << " length: " << dp.length() << std::endl;

	std::cout << "------------------区间变动--------------------" << std::endl;
	// 平移 n 天
	boost::gregorian::days dd(10);
	dp.shift(dd);
	std::cout << "begin: " << dp.begin() << " end: " << dp.end() << " length: " << dp.length() << std::endl;
	
	// 两段扩展 n 天 - 一共扩展 2 * n 天
	dp.expand(dd);
	std::cout << "begin: " << dp.begin() << " end: " << dp.end() << " length: " << dp.length() << std::endl;
	
	
	std::cout << "------------------日期包含--------------------" << std::endl;
	boost::gregorian::date d1(1999, 9, 9),  d2(2022, 2, 2);
	// 日期区间是否在日期后
	if (dp.is_after(d1))
	{
		std::cout << "日期区间 [" << dp.begin() << "," << dp.end() << ") 在日期" << d1 << "后" << std::endl;
	}
	else
	{
		std::cout << "日期区间 [" << dp.begin() << "," << dp.end() << ") 不在日期" << d1 << "后" << std::endl;
	}

	// 日期区间是否在日期前
	if (dp.is_before(d2))
	{
		std::cout << "日期区间 [" << dp.begin() << "," << dp.end() << ") 在日期" << d2 << "前" << std::endl;;
	}
	else
	{
		std::cout << "日期区间 [" << dp.begin() << "," << dp.end() << ") 不在日期" << d2 << "前" << std::endl;
	}

	// 日期区间是否包含另一个区间或日期
	boost::gregorian::date d3(2015, 5, 10);
	if (dp.contains(d3))
	{		
		std::cout << "日期区间 [" << dp.begin() << "," << dp.end() << ") 包含" << d3 << std::endl;
	}
	else
	{
		std::cout << "日期区间 [" << dp.begin() << "," << dp.end() << ") 不包含" << d3 << std::endl;
	}
	
	// 两个日期区间是否存在交集
	boost::gregorian::date_period dp2(boost::gregorian::date(2015, 5, 10), boost::gregorian::days(20));
	if (dp.intersects(dp2))
	{
		std::cout << "两个区间存在交集" << std::endl;
		boost::gregorian::date_period dp3 = dp.intersection(dp2);
		std::cout << "交集为: [" << dp3.begin() << "," << dp3.end() << ")" << std::endl;
	}
	else
	{
		std::cout << "两个区间不存在交集" << std::endl;
	}

	// 两个日期区间是否相邻
	if (dp.is_adjacent(dp2))
	{
		std::cout << "两个区间相邻" << std::endl;
	}
	else
	{
		std::cout << "两个区间不相邻" << std::endl;
	}

		
	// 两个区间并集
	boost::gregorian::date_period dp4 = dp.merge(dp2);
	std::cout << "区间并集: [" << dp4.begin() << ", " << dp4.end() << ")" << std::endl;

	// 合并两个区间
	boost::gregorian::date_period dp5(boost::gregorian::date(2022, 2, 2), boost::gregorian::days(100));
	boost::gregorian::date_period dp6 = dp.span(dp5);
	std::cout << "合并后区间: [" << dp6.begin() << ", " << dp6.end() << ")" << std::endl;


	return 0;
}
