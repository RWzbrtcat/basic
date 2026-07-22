#include <iostream>
#include <boost/algorithm/string.hpp>

int main()
{
	std::string str("FireEmblem Heroes\n");
	// 返回大写后的拷贝
	std::cout << boost::to_upper_copy(str);

	// 原字符串不变
	std::cout << str;

	// 字符串小写
	boost::to_lower(str);
	std::cout << str;

	return 0;
}
