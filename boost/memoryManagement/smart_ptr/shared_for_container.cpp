#include <iostream>
#include <vector>
#include <boost/smart_ptr.hpp>


typedef std::vector<boost::shared_ptr<int>> vs;

int main()
{
	// 声明一个拥有 10 个元素的容器
	vs v(10);

	int i = 0;
	for (auto pos = v.begin(); pos != v.end(); ++pos)
	{
		(*pos) = boost::make_shared<int>(++i);
		// 一次解引用操作获取 shared_ptr
		// 二次解引用获取 值
		std::cout << *(*pos) << " ";
	}
	std::cout << std::endl;

	boost::shared_ptr<int> p = v[9];
	*p = 100;
	std::cout << *v[9] << std::endl;
	return 0;
}
