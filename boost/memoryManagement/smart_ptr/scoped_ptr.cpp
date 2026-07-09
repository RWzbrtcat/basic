#include <iostream>
#include <boost/smart_ptr.hpp>

int main()
{
	// 构造一个 scoped_ptr 对象
	boost::scoped_ptr<std::string> sp(new std::string("test"));
	
	//判断是否为空 - 显式 bool 转换
	if (sp)
	{
		std::cout << *sp << std::endl;  // * 取字符串的内容
		std::cout << sp->size() << std::endl; // -> 取字符串的长度
	}

	// boost::scoped_ptr<std::string> sp2 = sp; // 错误，不允许拷贝

	return 0;
}
