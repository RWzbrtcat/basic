#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include <boost/utility/binary.hpp>

int main()
{
	boost::dynamic_bitset<> db1(4, BOOST_BINARY(1010));

	// 位运算
	db1[0] &= 1;
	db1[1] ^= 1;
	std::cout << db1 << std::endl;

	boost::dynamic_bitset<> db2(4, BOOST_BINARY(0101));
	std::cout << (db1 ^ db2) << std::endl;
	std::cout << (db1 | db2) << std::endl;

	return 0;
}
