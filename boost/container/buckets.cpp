#include <iostream>
#include <boost/unordered_set.hpp>
#include <boost/assign.hpp>
using namespace boost::assign;

int main()
{
	boost::unordered_set<int> s = list_of(1)(2)(3)(4);
	
	//buctet_count
	std::cout << s.bucket_count() << std::endl;

	s.rehash(100);
	std::cout << s.bucket_count() << std::endl;

	// 最大负载因子
	std::cout << s.max_load_factor() << std::endl;

	return 0;
}
