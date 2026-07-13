#include <iostream>
#include <boost/pool/pool.hpp>

int main()
{
	boost::pool pl(sizeof(int)); // 一个可分配 int 的内存池
	// 必须把 void* 转换成需要的类型
	int *p = static_cast<int*>(pl.malloc());
	// 判断是否分配成功
	if (p != nullptr)
	{
		// 判断 p 是否来自于 pl
		if (pl.is_from(p))
		{
			std::cout << "内存块 p 来自 pl" << std::endl;
		}
	}

	// 释放内存池分配的内存块
	pl.free(p);

	// 连续分配大量的内存
	for (int i = 0; i < 100; ++i)
	{
		pl.ordered_malloc(10);
	}

	return 0;
}
