#include <iostream>
#include <boost/exception/all.hpp>

int main()
{
	typedef boost::tuple<boost::errinfo_api_function, boost::errinfo_errno> err_group;
	
	try
	{
		throw boost::enable_error_info(std::out_of_range("out")) << err_group("syslogd", 874);
	}
	catch (boost::exception &e)
	{
		std::cout << boost::current_exception_diagnostic_information() << std::endl;
	}
	return 0;
}
