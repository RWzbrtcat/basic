#include <iostream>
#include <boost/assert.hpp>

double func(int x)
{
	BOOST_ASSERT_MSG( x != 0, "divided by zero"); // 断言参数非 0
	return 1 / x;
}


int main()
{
	auto y = func(0);
	return 0;
}
