#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>

int main()
{
	std::string str("readme.txt"); // 标准字符串
	
	// 判断后缀
	if (boost::ends_with(str, "txt"))
	{
		std::cout << boost::to_upper_copy(str) + " UPPER" << std::endl; // 大写
	}

	// 替换
	boost::replace_first(str, "readme", "followme");
	std::cout << str << std::endl;

	// 一个字符的 vector
	std::vector<char> v(str.begin(), str.end());
	std::vector<char> v2 = boost::to_upper_copy(boost::erase_first_copy(v, "txt"));

	for (auto ch : v2)
	{
		std::cout << ch;
	}
	std::cout << std::endl;

	return 0;
}
