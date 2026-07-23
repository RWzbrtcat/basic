#include <iostream>
#include <boost/xpressive/xpressive.hpp>

int main()
{
	std::string str("readme.txt");

	boost::xpressive::sregex reg1 = boost::xpressive::sregex::compile("(.*)(me)");
	boost::xpressive::sregex reg2 = boost::xpressive::sregex::compile("(t)(.)(t)");

	std::cout << boost::xpressive::regex_replace(str, reg1, "manual") << std::endl;
	std::cout << boost::xpressive::regex_replace(str, reg1, "$1you") << std::endl;
	std::cout << boost::xpressive::regex_replace(str, reg1, "$&$&") << std::endl;
	std::cout << boost::xpressive::regex_replace(str, reg2, "$1N$3") << std::endl;

	str = boost::xpressive::regex_replace(str, reg2, "$1$3");
	std::cout << str << std::endl;

	return 0;
}
