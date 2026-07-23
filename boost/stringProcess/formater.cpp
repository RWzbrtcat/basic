#include <iostream>
#include <boost/xpressive/xpressive.hpp>
#include <boost/algorithm/string.hpp>

struct formater
{
	std::string operator()(boost::xpressive::cmatch const &m) const
	{
		return boost::to_upper_copy(m[0].str());
	}
};

int main()
{
	char str[] = "*Link*||+Mario+||Zelda!!!||Metroid||";

	boost::xpressive::cregex reg = boost::xpressive::cregex::compile("\\w+", boost::xpressive::cregex::icase);

	std::cout << boost::xpressive::regex_replace(str, reg, formater()) << std::endl;

	return 0;
}
