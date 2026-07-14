#include <iostream>
#include <vector>
#include <deque>
#include <boost/assign.hpp>
using namespace boost::assign;

int main()
{
	std::vector<int> v = list_of(1)(2)(3)(4)(5);
	for (auto &x: v)
	{
		std::cout << x << " ";
	}
	std::cout << std::endl;
	
	// 逗号 和 括号混合使用，需要将整个 list_of 表达式用括号括起来
	std::deque<std::string> d = (list_of("power")("bomb"),"suit");
	for (auto &x: d) std::cout << x << " ";
	std::cout << std::endl;


	return 0;
}
