#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

class uuid_t : public boost::uuids::uuid
{
private:
	// 随机生成器
	static boost::uuids::random_generator& rand_uuid()
	{
		static boost::uuids::random_generator gen;
		return gen;
	}
	// 字符串生成器
	static boost::uuids::string_generator& string_uuid()
	{
		static boost::uuids::string_generator gen;
		return gen;
	}

public:
	// 默认构造函数，生成随机 UUID
	uuid_t() : uuid(rand_uuid()()) {}
	// 0 值的 UUID 构造函数
	uuid_t(int) : uuid(boost::uuids::nil_uuid()){}
	// 字符串构造函数
	uuid_t(const char* str) : uuid(string_uuid()(str)){}
	// 名字生成器构造函数
	uuid_t(const boost::uuids::uuid& u, const char* str) : uuid(boost::uuids::name_generator(u)(str)){}

	// 拷贝构造函数
	explicit uuid_t(const boost::uuids::uuid& u): uuid(u) {}

	// 转换到 uuid 类型
	operator uuid() 
	{
		return static_cast<boost::uuids::uuid&>(*this);
	}

	// 常函数，转换到 const uuid 类型
	operator uuid() const
	{
		return static_cast<const boost::uuids::uuid&>(*this);
	}

};

int main()
{
	// 类的使用

	uuid_t u0 = 0; // 0 的 nil
	std::cout << u0.is_nil() << std::endl;

	uuid_t u1, u2;  // 随机构造
	std::cout << u1 << std::endl;
	std::cout << u2 << std::endl;

	// 字符串构造
	uuid_t u3("{01234567-89ab-cdef-0123-456789abcdef}");
	std::cout << u3 << std::endl;
	
	// 名字生成器构造
	std::cout << uuid_t(u3, "test name gen") << std::endl;

	return 0;
}

