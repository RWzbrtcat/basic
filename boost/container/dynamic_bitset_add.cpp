#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include <boost/utility/binary.hpp>

int main()
{
	boost::dynamic_bitset<> db(5, BOOST_BINARY(01001));

	db.push_back(true);
	std::cout << db.size() << std::endl;
	std::cout << db << std::endl;
	
	// 会使得 db 的大小增加一个 block 的长度
	db.append(BOOST_BINARY(101));
	std::cout << db.size() << std::endl;
	std::cout << db << std::endl;

	return 0;
}
