#include <iostream>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>

int main()
{
	typedef boost::tuple<int, double, std::string> my_tuple;

	my_tuple t1(1, 2.0, "string");
	std::cout << t1 << std::endl;

	std::cout << "输入 tuple: ";
	std::cin >> t1;

	std::cout << t1 << std::endl;
	return 0;
}
