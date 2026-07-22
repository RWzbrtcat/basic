#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/assign.hpp>
#include <vector>
#include <boost/utility/string_ref.hpp>

int main()
{
	std::vector<std::string> v = boost::assign::list_of("Smaus")("Link")("Zelda")("Mario");

	// 简单合并
	std::cout << boost::join(v, "+") << std::endl;

	// 带谓词的合并
	// 需要带字符 a
	std::cout << boost::join_if(v, "**", [](boost::string_ref s) { return boost::contains(s, "a"); } );
	std::cout << std::endl;
	return 0;
}
