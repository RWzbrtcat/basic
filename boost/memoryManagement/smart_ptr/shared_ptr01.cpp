#include <iostream>
#include <boost/smart_ptr.hpp>

int main()
{
	// 构造一个指向整数的 shared_ptr
	boost::shared_ptr<int> sp(new int(10));

	if (sp.unique())
	{
		std::cout << "sp 是该整数指针的唯一管理者" << std::endl;
	}
	else
	{
		std::cout << "存在其他的 shared_ptr 指向该整数" << std::endl;
	}
	
	// 赋值构造
	boost::shared_ptr<int> sp2 = sp;

	if (sp == sp2)
	{
		std::cout << "两者相同，引用计数为: " << sp.use_count() << std::endl;
	}

	// 使用解引用操作符修改被指对象
	*sp2 = 100;
	std::cout << "sp修改为: " << *sp << std::endl;
	

	// 停止 shared_ptr 的引用
	sp.reset();
	if (!sp)
	{
		std::cout << "sp 不持有任何指针" << std::endl;
	}

	return 0;
}
