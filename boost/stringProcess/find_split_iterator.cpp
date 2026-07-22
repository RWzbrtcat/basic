#include <iostream>
#include <boost/algorithm/string.hpp>

int main()
{
	std::string str("Smaus||samus||mario||||Link");

	// 查找迭代器定义
	typedef boost::find_iterator<std::string::iterator> string_find_iterator;

	// 声明查找迭代器变量
	string_find_iterator pos, end;

	for (pos = boost::make_find_iterator(str, boost::first_finder("samus", boost::is_iequal())); pos != end; ++ pos)
	{
		std::cout << "[" << *pos << "] ";
	}
	std::cout << std::endl;

	// 分割迭代器类型定义
	typedef boost::split_iterator<std::string::iterator> string_split_iterator;

	string_split_iterator p, endp;

	for (p = boost::make_split_iterator(str, boost::first_finder("||", boost::is_iequal())); p != endp; ++p)
	{
		std::cout << "[" << *p << "] ";
	}
	std::cout << std::endl;

	return 0;
}
