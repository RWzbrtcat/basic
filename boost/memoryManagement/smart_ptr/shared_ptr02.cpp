#include <iostream>
#include <boost/smart_ptr.hpp>


class shared{
private:
	boost::shared_ptr<int> p;
public:
	// 构造函数
	shared(boost::shared_ptr<int> p_) : p(p_){}
	// 输出 shared_ptr 的引用计数和指向的值
	void print()
	{
		std::cout << "count: " << p.use_count() << " v = " << *p << std::endl;
	}
};

// 使用 shared_ptr 作为函数参数，同样输出引用计数和引用的值
void print_func(boost::shared_ptr<int> p)
{
	std::cout << "count: " << p.use_count() << " v = " << *p << std::endl;
}

int main()
{
	boost::shared_ptr<int> p(new int(100));
	shared s1(p), s2(p);

	s1.print();
	s2.print();
	
	// 修改值
	*p = 20;
	print_func(p);

	s1.print();

	return 0;
}
