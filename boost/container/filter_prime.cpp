#include <iostream>
#include <boost/dynamic_bitset.hpp>

int main()
{
	int n;
	std::cin >> n;
	boost::dynamic_bitset<> db(n);

	// 置位为 1
	db.set();
	
	// 跳过 0 和 1
	for (auto i = db.find_next(1); i != boost::dynamic_bitset<>::npos; i = db.find_next(i))
	{
		for (auto j = db.find_next(i); j != boost::dynamic_bitset<>::npos; j = db.find_next(j))
		{
			if (j % i == 0)
			{
				db[j] = 0; // 被整除 j 不是质数
			}
		}
	}

	// 输出所有位为 1 的数字 - 质数
	for (auto i = db.find_next(1); i != boost::dynamic_bitset<>::npos; i = db.find_next(i))
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
	return 0;
}
