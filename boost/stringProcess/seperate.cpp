#include <iostream>
#include <queue>
#include <list>
#include <boost/algorithm/string.hpp>

int main()
{
	std::string str = "Samus,Link.Zelda::Mario=Luigi+zelda";
	std::deque<std::string> d;

	// 大小写无关的分割字符串
	boost::ifind_all(d, str, "zELDA"); 
	std::cout << d.size() << std::endl;
	for (auto &x: d)
	{
		std::cout << "[" << x << "] ";
	}
	std::cout << std::endl;
	
	// 存储 range 对象
	std::list<boost::iterator_range<std::string::iterator>> lst;
	// 使用标点分割
	boost::split(lst, str, boost::is_any_of(",.:=+"));
	
	for (auto &x: lst)
	{
		std::cout << "[" << x << "] ";
	}
	std::cout << std::endl;

	lst.clear();
	boost::split(lst, str, boost::is_any_of(".:="), boost::token_compress_on);
	for (auto &x: lst)
	{
		std::cout << "[" << x << "] ";
	}
	std::cout << std::endl;

	return 0;
}
