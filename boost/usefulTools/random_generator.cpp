#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

int main()
{
	// 随机生成器
	boost::uuids::random_generator rgen;

	boost::uuids::uuid u = rgen();
	std::cout << u.version() << std::endl;
	std::cout << u << std::endl;
	return 0;
}
