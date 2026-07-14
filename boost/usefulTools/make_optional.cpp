#include <iostream>
#include <boost/optional.hpp>

int main()
{
	auto x = boost::make_optional(5);
	std::cout << "x: " << *x << std::endl;

	auto y = boost::make_optional<double>((*x > 10), 1.0);
	if (!y)
	{
		std::cout << "no result" << std::endl;
	}

	return 0;
}
