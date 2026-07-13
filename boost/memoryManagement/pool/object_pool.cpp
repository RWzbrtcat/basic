#include <iostream>
#include <boost/pool/object_pool.hpp>


// 示范用的类
struct demo_class
{
public:
	int a, b, c;
	
	demo_class(int x = 1, int y = 2, int z = 3) : a(x), b(y), c(z) {}
};


int main()
{
	// 对象内存池
	boost::object_pool<demo_class> pl;

	auto p = pl.malloc();
	assert(pl.is_from(p));

	// p 指向的内存未经过初始化
	assert(p->a != 1 || p->b != 2 || p-> c != 3);
	
	// construct 构造对象，可以传递参数
	p = pl.construct(7, 8, 9);
	std::cout << p->a << " " << p->b << " " << p->c << std::endl;

	// 定义一个分配 string 对象的内存池
	boost::object_pool<std::string> pls;
	// 连续分配大量 string 对象
	for (int i = 0; i < 10; ++i)
	{
		std::string *ps = pls.construct("hello object_pool");
		std::cout << *ps << std::endl;
	}
	return 0;
}
