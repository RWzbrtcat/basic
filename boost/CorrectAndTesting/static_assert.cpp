#include <iostream>
#include <boost/static_assert.hpp>

template<typename T>
T my_min(T a, T b)
{
	// 仅支持 short 或 char 类型
	BOOST_STATIC_ASSERT(sizeof(T) < sizeof(int)); // 静态断言
	retrun a < b ? a : b;
}

int main()
{
	std::cout << my_min((short)1, (short)3); // OK
	std::cout << my_min(1, 4); // 编译器错误
	return 0;
}
