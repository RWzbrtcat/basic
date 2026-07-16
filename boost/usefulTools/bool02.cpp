#include <iostream>
#include <cassert>
#include <boost/operators.hpp>
#include <boost/core/explicit_operator_bool.hpp>

struct demo_a
{
	// 定义显式 bool 转型操作
	BOOST_EXPLICIT_OPERATOR_BOOL()
	
	// 定义 operator!
	bool operator!() const
	{
		return false;
	}
};

struct demo_b
{
	BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()
	bool operator!() const
	{
		return true;
	}
};

int main()
{
	demo_a a;
	demo_b b;
	assert(a && !b);
	// a > b; // 编译错误
	return 0;
}
