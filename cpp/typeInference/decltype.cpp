#include <iostream>


// decltype 不剥离任何东西，原封不动保留类型

int main()
{
	int x = 10;
	const int cx = x;
	const int& rx = x;

	decltype(x) a = 10; // int

	decltype(cx) b = 10; // const int

	decltype(rx) c = x; // const int&

	// decltype 特殊规则, 双括号产生左值引用
	decltype((x)) d = x; // int&
	d = 20;
	std::cout << "x " << x << "\n"; // 20
	
	return 0;
}
