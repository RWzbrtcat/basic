#include <iostream>
#include <boost/exception/all.hpp>

struct my_exception : virtual std::exception, virtual boost::exception
{};

int main()
{
	typedef boost::error_info<struct tag_err_no, int> err_no;
	typedef boost::error_info<struct tag_err_str, std::string> err_str;
	
	try
	{
		try
		{
			// 创建一个 my_exception 临时对象，并向其传递了 err_no 对象，存入错误码 10
			throw my_exception() << err_no(10); // 抛出异常，存储错误码
		}
		catch (my_exception& e) // 捕获异常
		{
			// 获得异常内部存储的信息
			std::cout << *boost::get_error_info<err_no>(e) << std::endl;
			std::cout << e.what() << std::endl;
			e << err_str("other info"); // 向异常追加信息
			throw; // 再次抛出异常，被第二个 try-catch 块捕获
		}
	}
	catch(my_exception& e)
	{
		std::cout << *boost::get_error_info<err_str>(e) << std::endl;
	}


	return 0;
}
