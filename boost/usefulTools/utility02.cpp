#include <iostream>
#include <boost/current_function.hpp>

void func()
{
	std::cout << BOOST_CURRENT_FUNCTION << std::endl;
	return;
}


int main()
{
	std::cout << __FUNCTION__ << std::endl;
	std::cout << BOOST_CURRENT_FUNCTION << std::endl;
	
	func();

	return 0;
}
