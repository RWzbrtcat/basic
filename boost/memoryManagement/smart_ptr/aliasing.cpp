#include <iostream>
#include <boost/smart_ptr.hpp>

int main()
{
	auto p1 = boost::make_shared<std::pair<int, int>>(0, 1);

	// 别名构造
	boost::shared_ptr<int> p2(p1, &p1->second);
	
	// 原引用计数增加 且 两者引用计数相同
	std::cout << "p1.count: " << p1.use_count() << std::endl;
	std::cout << "p2.count: " << p2.use_count() << std::endl;
	
	// 但 指向内容不同
	std::cout << "p1: " << p1.get() << std::endl;
	std::cout << "p2: " << p2.get() << std::endl;

	return 0;
}
