#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <boost/assign.hpp>
using namespace boost::assign;

int main()
{
	std::vector<int> vec;
	vec += 1, 2, 4, 3 * 3, 10; // 用 += 和 , 向容器填入数据
	std::cout << "vec.size: " << vec.size() << std::endl;

	std::set<std::string> s;
	s += "c", "cpp", "lua", "swift";
	std::cout << "s.size: " << s.size() << std::endl;

	std::map<int, std::string> mp;
	mp += std::make_pair(1, "one"), std::make_pair(2, "two");
	std::cout << "mp.size: " << mp.size() << std::endl;

	return 0;
}
