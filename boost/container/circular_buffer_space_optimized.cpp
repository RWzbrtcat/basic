#include <iostream>
#include <boost/circular_buffer.hpp>
#include <boost/assign.hpp>

int main()
{
	boost::circular_buffer_space_optimized<int> cb(10);
	boost::assign::push_back(cb)(1), 2, 3, 4;

	std::cout << cb.size() << std::endl;  // 输出 4
	std::cout << cb.capacity() << std::endl; // 输出 10




	return 0;
}
