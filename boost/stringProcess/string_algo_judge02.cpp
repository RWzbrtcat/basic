#include <iostream>
#include <boost/algorithm/string.hpp>


int main()
{
	std::string str1("Samus"), str2("samus");

	std::cout << boost::is_equal()(str1, str2) << std::endl;
	std::cout << boost::is_less()(str1, str2) << std::endl;
	return 0;
}

