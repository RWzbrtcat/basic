#include <iostream>
#include <boost/xpressive/xpressive.hpp>

int main()
{
	char str[] = "there is a power-suit item";
	
	boost::xpressive::cregex reg = boost::xpressive::cregex::compile("(power)-(.{4})");

	std::cout << std::boolalpha;
	// 可搜索到字符串
	std::cout << boost::xpressive::regex_search(str, reg) << std::endl;

	boost::xpressive::cmatch what;
	// 保存搜索结果
	boost::xpressive::regex_search(str, what, reg);
	// 三个表达式
	std::cout << what.size() << std::endl;

	std::cout << what[0] << " " << what[1] << " " << what[2] << std::endl;


	return 0;
}
