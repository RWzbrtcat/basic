#include <iostream>


// cpp14引入，用auto的语法，decltyoe的语义--完美转发返回类型


int main()
{
	int x = 10;
	const int cx = 10;
	const int& rx = 10;

	// int - 剥离 const
	auto f1 = [=]{ return cx; };
	
	// const int - 完整保留
	decltype(auto) f2 = [=]{ return cx; };
	
	// int - 引用被剥离
	auto f3 = [&]{ return rx; };
	
	// int&
	decltype(auto) f4 = [&]{ return rx; };

	return 0;
}
