#include <iostream>
#include <boost/exception/all.hpp>

struct my_err{}; // 某个自定义的异常类，未使用 boost::exception

int main()
{
	try
	{
		// 使用 enable_error_info 包装自定义异常
		throw boost::enable_error_info(my_err()) << boost::errinfo_errno(10);
	}
	catch(boost::exception &e) // 必须使用 boost::exception 来捕获
	{
		std::cout << *boost::get_error_info<boost::errinfo_errno>(e) << std::endl;
	}

	return 0;
}
