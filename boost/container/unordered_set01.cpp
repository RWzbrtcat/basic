#include <iostream>
#include <boost/unordered_set.hpp>

int main()
{
	// 初始化数据
	boost::unordered_set<int> s = {1, 2, 3, 4, 5};

	for (auto x: s)
	{
		std::cout << x << ", ";
	}
	std::cout << std::endl;
	// 获取容器大小
	std::cout << s.size() << std::endl;

	// 清空集合
	s.clear();
	// 判断集合是否为空
	std::cout << std::boolalpha << s.empty() << std::endl;

	// insert 函数 插入数据
	s.insert(8);
	s.insert(10);

	std::cout << s.size() << std::endl;
	// 查找元素
	std::cout << *s.find(8) << std::endl;

	// 删除元素
	std::cout << s.erase(10) << std::endl;

	return 0;
}
