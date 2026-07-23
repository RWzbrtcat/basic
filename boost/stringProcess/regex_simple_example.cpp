#include <iostream>
#include <boost/xpressive/xpressive.hpp>

int main()
{
	// C 字符串正则表达式对象
	boost::xpressive::cregex reg = boost::xpressive::cregex::compile("a.c");
	std::cout << std::boolalpha;
	std::cout << boost::xpressive::regex_match("abc", reg) << std::endl;
	std::cout << boost::xpressive::regex_match("a+c", reg) << std::endl;
	std::cout << boost::xpressive::regex_match("ac", reg) << std::endl;
	std::cout << boost::xpressive::regex_match("abd", reg) << std::endl;

	return 0;
}
