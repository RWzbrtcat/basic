#include <iostream>

/*
   万能引用，也成为未定义引用，如果一个变量或参数被声明为 T&&，并且需要推导 T 的类型，那么该变量或参数即为万能引用

*/

template <typename T>
class Demo{
public:
	void func1(T&& x) // 右值引用  因为实例化后 T 会固定成某一类型
	{
		std::cout << x << "\n";
		return;
	}

	template <typename U>
	void func2(U&& y) // 万能引用
	{
		std::cout << y << "\n";
		return;
	}
	
	// const 会剥夺万能引用的资格
	template <typename F>
	void func3(const F&& z) // 右值引用
	{
		std::cout << z << "\n";
		return;
	}
};


int main()
{
	int p = 10;
	Demo<int> demo; // T 被固定为 int
	demo.func1(20); 
	// demo.func1(p);	 // error

	demo.func2(30);
	demo.func2(p);

	demo.func3(40);
	// demo.func3(p); // error
	return 0;
}
