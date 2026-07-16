#include <iostream>
#include <boost/config.hpp>



int main()
{	
	// __LINE__ 是C标准中定义的内置宏，表示程序的行号
	std::cout << BOOST_STRINGIZE(__LINE__) << std::endl;
	// std::boolalpha 控制 bool 值的输入/输出格式
	std::cout << std::boolalpha << (std::string("11") == BOOST_STRINGIZE(__LINE__)) << std::endl;

	int x = 255;
	// 无法处理运行时的整型变量，只能把它转化为字面意义的字符串 - x
	std::cout << BOOST_STRINGIZE(x) << std::endl;
	return 0;
}
