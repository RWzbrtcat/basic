#include <iostream>
#include <boost/tuple/tuple.hpp>

typedef boost::tuple<int, double, std::string> my_tuple;

my_tuple func()
{
	return boost::make_tuple(1, 2.0, "string");
}

int main()
{
	int i;
	double d;
	std::string s;
	
	boost::tie(i, d, s) = func(); // 使用 tie 可以接收 tuple 的函数返回值

	std::cout << "i: " << i << std::endl;
	std::cout << "d: " << d << std::endl;
	std::cout << "s: " << s << std::endl;

	return 0;
}
