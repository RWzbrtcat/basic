#include <iostream>


// auto 会剥离引用和顶层 const

int main()
{
	int x = 10;
	const int cx = x;
	const int& rx = x;

	auto a = x;  // int
	std::cout << "a " << a << "\n"; // 10

	auto b = cx; // int
	b = 20;
	std::cout << "b " << b << "\n"; // 20

	auto c = rx; // int
	c = 30;
	std::cout << "c " << c << "\n"; // 30
	std::cout << "rx " << rx << "\n"; // 10

	auto& d = x; // int&
	d = 40;
	std::cout << "d " << d << "\n"; // 40
	std::cout << "x " << x << "\n"; // 40

	auto& e = x; // const int&  - 底层const保留
	std::cout << "e " << e << "\n"; // 40

	auto&& g = x; // int & - 万能引用 左值->右值引用
	g = 50;
	std::cout << "g " << g << "\n"; // 50
	std::cout << "x " << x << "\n"; // 50

	auto&& h = 10; // int&& - 万能引用 右值->右值引用
	std::cout << "h " << h << "\n"; // 10
}
