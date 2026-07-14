#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <boost/assign.hpp>
using namespace boost::assign;


int main()
{
	std::vector<int> v;
	push_back(v)(1)(2)(3);
	std::cout << "v.size: " << v.size() << std::endl;
	
	std::list<std::string> lst;
	push_front(lst)("c")("cpp");
	std::cout << "lst.size: " << lst.size() << std::endl;

	std::set<double> s;
	insert(s)(1.2)(3.14)(4.96)(5.20);
	std::cout << "s.size: " << s.size() << std::endl;

	std::map<int, std::string> mp;
	insert(mp)(1, "one")(2, "two");
	std::cout << "mp.size: " << mp.size() << std::endl;

	return 0;
}
