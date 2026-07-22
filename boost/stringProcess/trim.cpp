#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>


int main()
{
	boost::format fmt("|%s|\n");
	std::string str = " samus aran ";
	
	// 删除两端的空格
	std::cout << fmt % boost::trim_copy(str);
	// 删除左端的空格
	std::cout << fmt % boost::trim_left_copy(str);

	// 删除右端的空格
	std::cout << fmt % boost::trim_right_copy(str);

	std::string str2 = "2026 Happy New Year!!!";
	// 删除左端的数字
	std::cout << fmt % boost::trim_left_copy_if(str2, boost::is_digit());
	// 删除右端的标点符号
	std::cout << fmt % boost::trim_right_copy_if(str2, boost::is_punct());
	// 删除两端的标点、数字和空格
	std::cout << fmt % boost::trim_copy_if(str2, boost::is_punct() || boost::is_digit() || boost::is_space());

	return 0;
}
