#include <iostream>
#include <boost/utility.hpp>

int main()
{
	std::cout << BOOST_BINARY(0110) << std::endl;
	std::cout << BOOST_BINARY(0110 1100) << std::endl;
	std::cout << BOOST_BINARY(011110 010) << std::endl;

	std::cout << BOOST_BINARY_UL(010 0010) << std::endl;
	long long x = BOOST_BINARY_LL(1101);
	return 0;
}
