#include <iostream>
#include <boost/exception/all.hpp>

struct my_exception : virtual std::exception, virtual boost::exception
{};

int main()
{
	try
	{
		throw my_exception() << boost::errinfo_api_function("call api") << boost::errinfo_errno(101);
	}
	catch (boost::exception& e)
	{
		std::cout << *boost::get_error_info<boost::errinfo_api_function>(e) << std::endl;
		std::cout << *boost::get_error_info<boost::errinfo_errno>(e) << std::endl;
	}

	return 0;
}
