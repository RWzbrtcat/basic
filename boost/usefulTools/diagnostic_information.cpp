#include <iostream>
#include <boost/throw_exception.hpp>
#include <boost/exception/all.hpp>

struct my_err{};

int main()
{
	try
	{
		throw boost::enable_error_info(my_err()) << boost::errinfo_errno(10) << boost::errinfo_api_function("fopen");
	}
	catch(boost::exception& e)
	{
		std::cout << boost::diagnostic_information(e) << std::endl;
	}

	try
	{
		BOOST_THROW_EXCEPTION(std::logic_error("logic")); // 必须是标准异常
	}
	catch (boost::exception& e)
	{
		std::cout << boost::diagnostic_information(e) << std::endl;
	}
	return 0;
}
