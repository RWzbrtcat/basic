#include <iostream>
#include <boost/smart_ptr.hpp>

// 首先实现一个抽象基类
class abstract{
public:
	virtual void f() = 0;
	virtual void g() = 0;
protected:
	virtual ~abstract() = default; 
};

// 定义 abstract 的实现子类
class impl: public abstract
{
public:
	impl() = default;
	virtual ~impl() = default;

public:
	virtual void f()
	{
		std::cout << "class impl f" << std::endl;
	}
	virtual void g()
	{
		std::cout << "class impl g" << std::endl;
	}
};

// 定义工厂函数，返回基类的 shared_ptr
boost::shared_ptr<abstract> create()
{
	return boost::make_shared<impl>();
}

int main()
{
	// 工厂函数创建对象
	auto p = create();
	p->f();
	p->g();

	return 0;
}

