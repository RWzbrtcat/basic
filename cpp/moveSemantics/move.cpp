#include <iostream>

// 移动语义
/*
  定义一个空类，编译器会自动生成构造函数、析构函数、拷贝构造函数以及拷贝赋值运算符
  cpp11 之后，除上述之外，还会自动生成移动构造函数和移动赋值运算符

  如果我们定义了拷贝构造函数/拷贝赋值运算符/析构函数，
  那么编译器就不会自动生成构造函数和移动赋值运算符

  如果定义了移动构造函数，那么编译器就不会生成移动赋值运算符，反之亦然，
  在这种情况下，调用移动赋值运算符，会产生编译错误
*/
class Demo{
public:
	Demo(): age{18}
	{
		name = new char[] {"xiaoMing"};
	}
	

	// 实现移动构造函数
	Demo(Demo&& rdemo) noexcept : age { std::move(rdemo.age) }
	{
		// 转移数据
		name = rdemo.name;

		rdemo.age = 0; // 清楚被转移对象的数据
		rdemo.name = nullptr;
	}

	// 移动赋值运算符
	Demo& operator=(Demo&& rdemo) noexcept
	{
		age = rdemo.age;
		name = rdemo.name;

		rdemo.age = 0;
		rdemo.name = nullptr;

		return *this;
	}

	~Demo()
	{
		if (nullptr != name)
		{
			delete[] name;
			name = nullptr;
		}
	}

private:
	int age;
	char* name;
};


int main()
{
	Demo demo1{};
	Demo demo2{ std::move(demo1) }; // 通过移动构造函数创建新对象
	return 0;
}
