#include <iostream>
#include <boost/algorithm/string.hpp>

int main()
{
	std::string str("Power Bomb");
	
	// 检测后缀
	std::cout << boost::iends_with(str, "bomb") << std::endl;
	std::cout << boost::ends_with(str, "bomb") << std::endl;
	
	// 检测前缀
	std::cout << boost::istarts_with(str, "pow") << std::endl;
	std::cout << boost::starts_with(str, "pow") << std::endl;

	// 包含关系
	std::cout << boost::icontains(str, "bo") << std::endl;
	std::cout << boost::contains(str, "bo") << std::endl;

	// 相等判断
	std::string str2 = boost::to_lower_copy(str);
	std::cout << boost::iequals(str, str2) << std::endl;
	std::cout << boost::equals(str, str2) << std::endl;
	
	// 字符串比较
	std::string str3("power suit");
	std::cout << boost::ilexicographical_compare(str, str3) << std::endl;
	std::cout << boost::lexicographical_compare(str, str3) << std::endl;

	// 检测字符串是否均小写
	std::cout << boost::all(str2.substr(0, 5), boost::is_lower()) << std::endl;

	return 0;
}
