#include <iostream>
#include <boost/pool/singleton_pool.hpp>

// 用于标记的空类
struct pool_tag{};

// 第一个参数 Tag 用于标记不同的单件，可以是空类
// 第二个参数 RequestedSize 等同于 pool 构造函数中的 requested_size，可以指示 pool 分配的内存块的大小
typedef boost::singleton_pool<pool_tag, sizeof(int)> spl; // 定义内存池

int main()
{
	// 分配一个整数内存块
	int *p = (int *)spl::malloc();
	
	// 释放内存
	spl::release_memory();
	return 0;
}
