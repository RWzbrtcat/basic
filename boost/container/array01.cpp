#include <iostream>
#include <boost/array.hpp>

int main()
{
	// 创建一个大小为 10 的数组
	boost::array<int, 10> arr;

	arr[0] = 1; // operator[]
	arr.back() = 10;
	std::cout << arr[arr.max_size() - 1] << std::endl;

	// 将所有数组元素赋值为 777
	arr.assign(777);
	for (auto &x: arr) std::cout << x << ",";
	std::cout << std::endl;

	// 获得原始数组指针
	int *p = arr.c_array();
	*(p + 5) = 253;
	std::cout << arr[5] << std::endl;

	arr.at(8) = 666;
	std::cout << arr[8] << std::endl;

	return 0;
}
