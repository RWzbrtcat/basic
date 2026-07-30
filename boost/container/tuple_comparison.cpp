#include <iostream>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>

int main()
{
	typedef boost::tuple<int, double, std::string> my_tuple;

	my_tuple t1 = boost::make_tuple(1, 100.0, std::string("abc"));
	my_tuple t2 = boost::make_tuple(1, 200.0, std::string("def"));
	
	std::cout << std::boolalpha << (t1 < t2) << std::endl;

	my_tuple t3(t2);
	std::cout << (t2 == t3) << std::endl;
	return 0;
}
