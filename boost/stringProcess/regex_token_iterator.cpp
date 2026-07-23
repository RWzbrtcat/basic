#include <iostream>
#include <boost/xpressive/xpressive.hpp>

int main()
{
	char str[] = "*LINK*||+Mario+||Zelda!!!||Metroid";

	// 查找所有的单词，忽略标点符号
	boost::xpressive::cregex reg = boost::xpressive::cregex::compile("\\w+", boost::xpressive::icase);

	boost::xpressive::cregex_token_iterator pos(str, str + strlen(str), reg);
	for (; pos != boost::xpressive::cregex_token_iterator(); ++pos)
	{
		std::cout << "[" << *pos << "] ";
	}
	std::cout << std::endl;

	// 使用分隔符的正则表达式，分隔符是 \\

	boost::xpressive::cregex split_reg = boost::xpressive::cregex::compile("\\|\\|");
	pos = boost::xpressive::cregex_token_iterator(str, str + strlen(str), split_reg, -1);
	for (; pos != boost::xpressive::cregex_token_iterator(); ++pos)
	{
		std::cout << "[" << *pos << "] ";
	}
	std::cout << std::endl;
	return 0;
}
