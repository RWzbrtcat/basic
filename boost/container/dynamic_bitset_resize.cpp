#include <iostream>
#include <boost/dynamic_bitset.hpp>

int main()
{
	boost::dynamic_bitset<> db;
		
	db.resize(10, true); // 扩展为 10 个二进制位，值为 1
	std::cout << db << std::endl;

	db.resize(5); // 缩小容量为 5
	std::cout << db << std::endl;
	return 0;
}
