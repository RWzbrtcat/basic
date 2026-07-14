#include <iostream>
#include <boost/assign.hpp>
#include <vector>
#include <deque>
using namespace boost::assign;

int main()
{
	std::vector<int> v = list_of(1).repeat(3, 2)(3)(4)(5);
	for (auto &x: v) std::cout << x << " ";
	std::cout << std::endl;
	
	std::multiset<int> ms;
	insert(ms).repeat_fun(5, &rand),repeat(2, 1), 10;
	for(auto &x: ms) std::cout << x << " ";
	std::cout << std::endl;

	std::deque<int> d;
	push_front(d).range(v.begin(), v.begin() + 5);
	for(auto &x: d) std::cout << x << " ";
	std::cout << std::endl;

	return 0;
}
