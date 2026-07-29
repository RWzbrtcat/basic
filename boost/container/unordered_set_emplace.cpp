#include <iostream>
#include <boost/unordered_set.hpp>

int main()
{
	typedef std::complex<double> complex_t; // 复数类型
	boost::unordered_set<complex_t> s;
	
	s.emplace(1.0, 2.0);
	s.emplace(3.0, 4.0);

	for (auto &x: s)
	{
		std::cout << x << ", ";
	}
	std::cout << std::endl;
	
	// 在容器前端插入，不保证位置
	s.emplace_hint(s.begin(), 5.0, 6.0);
	for (auto &x: s)
	{
		std::cout << x << ", ";
	}
	std::cout << std::endl;


	return 0;
}
