#define BOOST_ENABLE_ASSERT_HANDLER
#include <iostream>
#include <boost/format.hpp>
#include <boost/assert.hpp>


namespace boost
{
	void assertion_failed(char const *expr, char const *function, char const *file, long line) { }
	void assertion_failed_msg(char const* expr, char const *msg, char const *function, char const *file, long line)
	{
		boost::format fmt("Assertion failed!\n Expression: %s\n Function: %s\n File: %s\n Line: %ld\n Msg: %s\n\n");
		fmt % expr % function % file % line % msg;
		std::cout << fmt;
	}
}


double func(int x)
{
	BOOST_ASSERT_MSG(x != 0, "divided by zero");
	return 1.0 / x;
}


int main()
{
	func(0);

	return 0;
}
