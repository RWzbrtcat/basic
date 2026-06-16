#include <iosrteam>

/*
   顶层 const 表示指针本身是个常量 - 常量指针
   底层 const 表示指针所指的对象是一个常量 - 指针常量
*/


int main()
{
	int i = 0;
	// 从右向前读
	// 距离p1最近的符号是const，意味着p1本身是一个常量对象
	// 对象的类型由声明符的其他部分确定
	// 下一个符号是 *，意思是p1是一个常量指针
	// int 表明是指向int的常量指针

	// 从右往左读  
	// 指针 常量  -- 常量指针
	int *const p1 = &i; // 不能改变 p1 的值，这是一个顶层 const

	// 在没有指针的前提下，顶层const可以表示任意的对象是常量
	const int ci = 42; // 不能改变 ci 的值，这是一个顶层 const
	
	// 常量 指针 --  指针常量
	const int* p2 = &ci; // 允许改变 p2 的值，这是一个底层 const
	return 0;
}
