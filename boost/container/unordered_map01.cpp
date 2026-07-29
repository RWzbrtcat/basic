#include <iostream>
#include <boost/unordered_map.hpp>
#include <boost/assign.hpp>

using namespace boost::assign;


int main()
{
	// 使用 assign 初始化
	boost::unordered_map<int, std::string> umap = map_list_of(1, "one")(2, "two")(3, "three");
	
	// insert 函数
	umap.insert(std::make_pair(4, "four"));
	// operator[] 访问元素
	std::cout << umap[4] << std::endl;

	umap[15] = "fifteen";
	umap[18] = "eighteen";

	for (auto p = umap.begin(); p != umap.end(); ++p)
	{
		std::cout << p->first << "-" << p->second << ", ";
	}
	std::cout << std::endl;

	std::cout << umap.size() << std::endl;


	return 0;
}
