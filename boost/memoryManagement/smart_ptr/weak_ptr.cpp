#include <iostream>
#include <boost/smart_ptr.hpp>

int main()
{
	boost::shared_ptr<int> sp(new int(10));
	std::cout << "引用计数: " << sp.use_count() << std::endl;

	// 从 shared_ptr 创建 weak_ptr
	boost::weak_ptr<int> wp(sp);
	if (!wp.empty())
	{
		std::cout << "创建 weak_ptr 后引用计数: " << wp.use_count() << std::endl;
	}
	
	if (!wp.expired())
	{
		boost::shared_ptr<int> sp2 = wp.lock(); // 获得一个 shared_ptr
		*sp2 = 100;
		std::cout << "wp.lock后引用计数: " << wp.use_count() << std::endl;
	}

	// sp2 退出作用域后自动析构，引用计数变为 1
	std::cout << "sp2 退出作用域后引用计数: " << wp.use_count() << std::endl;

	// 重置指针
	sp.reset();
	if (wp.expired())
	{
		std::cout << "weak_ptr 失效" << std::endl;
	}

	return 0;
}
