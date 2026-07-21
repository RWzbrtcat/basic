#include <iostream>
#include <boost/format.hpp>

int main()
{
	// 类似 printf() 语法
	std::cout << boost::format("%s: %d + %d = %d\n") %"sum" % 1 % 2 % (1 + 2);
	
	// 预先创建一个 format 对象  %n% 指定参数的位置，可分多次输入
	boost::format fmt("(%1% + %2%) * %2% = %3%\n");
	fmt % 2 % 5; // 输入 %1% 和 %2%
	fmt % ((2 + 5) * 5); // 输入 %3% 
	std::cout << fmt.str() << std::endl;
	return 0;
}
