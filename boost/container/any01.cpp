#include <iostream>
#include <boost/any.hpp>
#include <vector>

int main()
{
	boost::any a(100); // 创建一个 any 对象，将其初始化为一个整数

	a = std::vector<std::vector<int>>(); // any 存储一个二维 vector
	a = std::string("char"); // any 存储一个 string 字符串

	// any_cast 取值
	// 必须要知道内部值得确切类型
	std::cout << boost::any_cast<std::string>(a) << std::endl;

	return 0;
}
