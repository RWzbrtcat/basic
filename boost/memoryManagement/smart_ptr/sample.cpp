#include "sample.hpp"
#include <iostream>

// 内部类的实现
class sample::impl{
public:
	void print()
	{
		std::cout << "impl print" << std::endl;
	}
};

// 构造函数初始化 shared_ptr
sample::sample():p(new impl){}

// 调用 pimpl 实现 print()
void sample::print()
{
	p->print();
}
