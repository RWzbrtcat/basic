#include <iostream>
#include <boost/utility/string_ref.hpp>


int main()
{

	std::cout << " ------------字符串构造--------------" << std::endl;
	const char* ch = "Days of Future Past";

	std::string str(ch); // 标准字符串，有拷贝成本

	// 字符数组构造，零拷贝
	boost::string_ref s1(ch);
	boost::string_ref s2(str); // 标准字符串构造，零拷贝
	std::cout << "s1: " << s1 << "   "  << "s2: " << s2 << std::endl;

	// 截取部分字符串构造
	boost::string_ref s3(ch, 4);
	std::cout << "s3: " << s3 << std::endl;

	std::cout << "------------字符串使用----------------" << std::endl;
	if (!s1.empty())
	{
		std::cout << "size: " << s1.size() << std::endl;
	}
	for (auto &x: s1)
	{
		std::cout << x;
	}
	std::cout << std::endl;
	
	// 类似容器操作
	std::cout << "str.fornt: " <<str.front() << "  str[3]: " << str[3] << std::endl;
	// 查找操作
	std::cout << "o 的位置: " << str.find('0') << std::endl;

	// 获取子串
	auto substr = s1.substr(2, 4);
	std::cout << "substr: " << substr << std::endl;
	
	// 清空字符串
	s1.clear();
	if (s1.empty())
	{
		std::cout << "s1 已清空" << std::endl;
	}
	
	// 删除前5个字符
	s2.remove_prefix(5);
	std::cout << "s2: " << s2 << std::endl;
	std::cout << "以 of 开头: " <<s2.starts_with("of") << std::endl;
	// 删除后5个字符
	s2.remove_suffix(5);
	std::cout << "s2: " << s2 << std::endl;
	std::cout << "以 Future 结尾: " << s2.ends_with("Future") << std::endl;



	return 0;
}
