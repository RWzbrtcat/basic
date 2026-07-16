#include <iostream>
#include <boost/lexical_cast.hpp>

template<typename T>
bool num_valid(const char* str)
{
	T tmp;
	return boost::conversion::try_lexical_convert(str, tmp);
}


int main()
{
	// 验证数字字符串的合法性
	std::cout << num_valid<double>("3.14") << std::endl;
	std::cout << num_valid<int>("11111") << std::endl;

	return 0;
}
