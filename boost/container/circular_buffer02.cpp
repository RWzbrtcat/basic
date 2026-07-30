#include <iostream>
#include <boost/assign.hpp>
#include <boost/circular_buffer.hpp>
using namespace boost::assign;

int main()
{
	boost::circular_buffer<int> cb = (list_of(1), 2, 3, 4, 5);
	// 判断 缓冲区是否已满
	if (cb.full())
	{
		std::cout << "缓冲区已满" << std::endl;
	}

	// 获取线性数组
	int *p = cb.linearize();
	std::cout << p[0] << std::endl;

	// 判断缓冲区是否线性化
	if(cb.is_linearized())
	{
		std::cout << "缓冲区已线性化" << std::endl;
	}

	// 从第三个位置开始旋转
	cb.rotate(cb.begin() + 2);
	for (auto p = cb.begin(); p != cb.end(); ++p)
	{
		std::cout << *p << " ";
	}
	std::cout << std::endl;
	return 0;
}
