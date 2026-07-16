#include <iostream>
#include <cassert>
#include <boost/operators.hpp>

struct demo_a
{
	// 隐式转换为 true
	operator bool() const
	{
		return true;
	}
};

struct demo_b
{
	// 隐式转换为 false
	operator bool() const
	{
		return false;
	}
};


int main()
{
	demo_a a;
	demo_b b;
	assert(a != b); // 隐式转换为 bool 执行比较
	assert(a > b); // true > false
	return 0;
}
