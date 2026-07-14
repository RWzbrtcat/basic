#include <iostream>
#include <map>
#include <boost/assign.hpp>
using namespace boost::assign;


int main()
{
	std::map<int, std::string> mp = map_list_of(1, "one")(2, "two");
	for (auto &v: mp)
	{
		std::cout << v.first << ", " << v.second << std::endl;
	}
	return 0;
}
