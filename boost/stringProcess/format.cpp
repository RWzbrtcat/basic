#include <iostream>
#include <boost/format.hpp>
#include <iomanip>

int main()
{	
	// 声明 format 对象
	boost::format fmt("%1% %2% %3% %2% %1% \n");
	std::cout << fmt % 4 % 5 % 6;
	
	// 将第二个参数输入固定为 10
	fmt.bind_arg(2, 10);
	std::cout << fmt % 7 % 8; // 输入其余两个参数

	fmt.clear(); // 清空缓存，但绑定的参数不变

	// 在 % 操作符中使用 group() 指定输入输出流操作符的第一个参数显式为八进制
	std::cout << fmt % boost::io::group(std::showbase, std::oct, 111) % 333;

	// 清除所有绑定参数
	fmt.clear_binds();

	// 设置第一个格式化项，十六进制，宽度为 8 右对齐，不足为用 * 填充
	fmt.modify_item(1, boost::io::group(std::hex, std::right, std::showbase, std::setw(8), std::setfill('*')));
	std::cout << fmt % 66 % 77 % 88;

	return 0;
}
