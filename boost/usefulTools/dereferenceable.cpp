#include <iostream>
#include <boost/operators.hpp>

template<typename T>
class my_smart_ptr : public boost::dereferenceable<my_smart_ptr<T>, T* > // 必须 public 继承
{
	T *p; // 内部保存的指针
public:
	// 构造和析构函数
	my_smart_ptr(T *x) : p(x){}
	~my_smart_ptr(){ delete p; }
	// 定义 operator* 操作，必须是常函数
	T& operator*() const
	{
		return *p;
	}
};


int main()
{
	// 使用 my_smart_ptr
	my_smart_ptr<std::string> p(new std::string("123"));
	std::cout << *p << std::endl;
	return 0;
}
