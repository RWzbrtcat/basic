#include <iostream>
#include <type_traits.hpp>
#include <boost/core/lightweight_test_trait.hpp>

int main()
{
	BOOST_TEST_TRAIT_TRUE((is_integral<int>)); // int 是整数
	BOOST_TEST_TRAIT_FALSE((is_function<int>)); // int 不是函数

	return boost::report_errors();
}
