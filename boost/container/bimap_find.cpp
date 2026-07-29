#include <iostream>
#include <boost/bimap.hpp>
#include <boost/assign.hpp>
using namespace boost::assign;

int main()
{
	typedef boost::bimap<int, std::string> bm_t;
	bm_t bm = boost::assign::list_of<bm_t::relation>(1, "mario")(2, "peach");

	// 左视图查找键1
	auto pos = bm.left.find(1);
	std::cout << pos->first << "---" << pos->second << std::endl;

	// 右视图查找 peach
	auto pos2 = bm.right.find("peach");
	std::cout << pos2->first << "---"<< pos2->second << std::endl; 
	return 0;
}
