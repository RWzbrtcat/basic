#include <iostream>
#include <boost/algorithm/string.hpp>

int main()
{
	char c = 'a';
	std::cout << boost::is_space()(' ') << std::endl;
	std::cout << boost::is_alnum()(c) << std::endl;

	std::cout << boost::is_xdigit()('a') << std::endl;

	return 0;
}
