#include <iostream>
#include <boost/dynamic_bitset.hpp>
#include <boost/utility/binary.hpp>

int main()
{
	boost::dynamic_bitset<> db1(4, BOOST_BINARY(0101));
	std::cout << std::boolalpha;
	
	// 测试二进制位
	std::cout << db1.test(0) << std::endl;
	std::cout << db1.any() << std::endl;
	std::cout << db1.none() << std::endl;
	std::cout << db1.count() << std::endl;
	
	// 反转二进制位
	db1.flip();
	std::cout << db1 << std::endl;
	db1.set(); // 置所有位为 1
	std::cout << db1 << std::endl;
	// 置所有位为 0
	db1.reset();
	std::cout << db1 << std::endl;
	
	db1.set(1, 1); // 置 db[1] 为 1
	std::cout << db1 << std::endl;

	// 查找
	auto pos = db1.find_first();
	std::cout << pos << std::endl;

	pos = db1.find_next(pos);
	std::cout << pos << std::endl;

	return 0;
}
