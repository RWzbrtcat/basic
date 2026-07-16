#include <iostream>
#include <boost/operators.hpp>

// my_smart_array 公开继承 indexable   下标操作符的类型是 int   operator[]的返回值的类型是 T&
template<typename T>
class my_smart_array : public boost::indexable<my_smart_array<T>, int, T&>
{
	T* p; // 保存动态数组指针
public:
	typedef my_smart_array<T> this_type;
	typedef T* iter_type; // 迭代器类型

	// 构造函数和析构函数
	my_smart_array(T *x): p(x){}
	~my_smart_array(){ delete[] p; }

	friend iter_type operator+(const this_type& a, int n)
	{
		return a.p + n; // 返回一个迭代器类型，可以使用 operator* 操作
	}
};


int main()
{
	my_smart_array<double> ma(new double[10]);
	ma[0] = 1.0; 	// operator[] 运算
	*(ma + 1) = 2.0; // 指针算术运算
	std::cout << ma[1] << std::endl;
	return 0;
}
