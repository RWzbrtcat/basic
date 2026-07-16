
#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <vector>


int main()
{
	// 声明一个 uuid 对象
	boost::uuids::uuid u;
	
	// 长度输出
	std::cout << u.static_size() << std::endl;
	std::cout << u.size() << std::endl;

	std::vector<unsigned char> v(16, 7);
	std::copy(v.begin(), v.end(), u.begin());
	std::cout << u << std::endl;

	// 使用标准算法 fill_n 直接操纵数组
	std::fill_n(u.data + 10, 6, 8);
	std::cout << u << std::endl;

	std::cout << "变体号: " << u.variant() << std::endl;

	std::cout << "算法类型: " << u.version() << std::endl;

	std::cout << u.is_nil() << std::endl;


	return 0;
}
