#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>


int main()
{
	// 首先生成一个组织的 UUID
	boost::uuids::uuid www_xxx_com = boost::uuids::string_generator()("0123456789abcdef0123456789abcdef");

	// 构造名字生成器
	boost::uuids::name_generator ngen(www_xxx_com);
	
	// 为名字 mario 生成 UUID
	boost::uuids::uuid u1 = ngen("mario");
	std::cout << u1 << std::endl;
	std::cout << u1.version() << std::endl;

	// 为名字 link 生成 UUID
	boost::uuids::uuid u2 = ngen("link");
	std::cout << u2 << std::endl;
	return 0;
}
