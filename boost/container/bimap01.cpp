#include <iostream>
#include <boost/bimap.hpp>

int main()
{
	boost::bimap<int, std::string> bm;
	
	// 左视图
	bm.left.insert(std::make_pair(1, "111"));
	bm.left.insert(std::make_pair(2, "222"));

	// 右视图
	bm.right.insert(std::make_pair("string", 10));
	bm.right.insert(std::make_pair("bimap", 20));

	// 对左视图使用迭代器迭代
	for (auto pos = bm.left.begin(); pos != bm.left.end(); ++pos)
	{
		std::cout << "left[" << pos->first << "]=" << pos->second << std::endl;
	}

	return 0;
}
