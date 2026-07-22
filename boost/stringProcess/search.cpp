#include <iostream>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>

int main()
{
	boost::format fmt("|%s|. pos = %d\n");
	std::string str = "Long long ago, there was a king.";

	// 迭代器区间
	boost::iterator_range<std::string::iterator> rge;

	// 找第一次出现
	rge = boost::find_first(str, "long");
	std::cout << fmt % rge % (rge.begin() - str.begin());

	// 大小写无关找第一次出现
	rge = boost::find_first(str, "long");
	std::cout << fmt % rge % (rge.begin() - str.begin());

	// 找第三次出现
	rge = boost::find_nth(str, "ng", 2);
	std::cout << fmt % rge % (rge.begin() - str.begin());

	// 取前四个字符
	rge = boost::find_head(str, 4);
	std::cout << fmt % rge % (rge.begin() - str.begin());
	
	// 取末尾 5 个字符
	rge = boost::find_tail(str, 5);
	std::cout << fmt % rge % (rge.begin() - str.begin());

	// 找不到
	rge = boost::find_first(str, "samus");
	if (rge.empty() && !rge)
	{
		std::cout << "can not find" << std::endl;
	}

	return 0;
}
