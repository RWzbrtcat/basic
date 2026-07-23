#include <iostream>
#include <boost/xpressive/xpressive.hpp>

int main()
{
	std::string str("Power-bomb, power-suit, pOWER-beam all item\n");
	
	boost::xpressive::sregex reg = boost::xpressive::sregex::compile("power-(.{4})", boost::xpressive::icase);

	boost::xpressive::sregex_iterator pos(str.begin(), str.end(), reg);
	boost::xpressive::sregex_iterator end;

	for (; pos != end; ++pos)
	{
		std::cout << "[" << (*pos)[0] << "] ";
	}
	std::cout << std::endl;	

	return 0;
}
