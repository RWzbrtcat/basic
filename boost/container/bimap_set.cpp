#include <iostream>
#include <boost/bimap/unordered_multiset_of.hpp>
#include <boost/bimap.hpp>

template<typename T>
void print(T &m)
{
	for (auto &x: m)
	{
		std::cout << x.first << "<-->" << x.second << std::endl;
	}
}


int main()
{
	// 声明一个无序多值的 bimap
	boost::bimap<boost::bimaps::unordered_multiset_of<int>, boost::bimaps::unordered_multiset_of<std::string>> bm;

	bm.left.insert(std::make_pair(1, "111"));
	bm.left.insert(std::make_pair(2, "222"));
	bm.left.insert(std::make_pair(2, "555"));

	bm.right.insert(std::make_pair("string", 10));
	bm.right.insert(std::make_pair("bimap", 20));
	bm.right.insert(std::make_pair("bimap", 2));

	print(bm.left);

	return 0;
}
