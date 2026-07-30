#include <iostream>
#include <boost/circular_buffer.hpp>


int main()
{
	// 声明一个大小为 5 的循环缓冲区
	boost::circular_buffer<int> cb(5);
	if(cb.empty())
	{
		std::cout << "缓冲区无数据" << std::endl;
	}

	cb.push_back(1);
	cb.push_front(2);

	std::cout << cb.front() << std::endl;
	
	// 向前端添加元素 3
	cb.insert(cb.begin(), 3);

	for (auto pos = cb.begin(); pos != cb.end(); ++pos)
	{
		std::cout << *pos << ", ";
	}
	std::cout << std::endl;

	cb.pop_front(); // 弹出首元素 3
	cb.pop_back(); // 弹出尾元素 1
	std::cout << cb[0] << std::endl; // 输出元素 2

	return 0;
}
