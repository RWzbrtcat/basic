#include <iostream>
#include <boost/lexical_cast.hpp>


int main()
{
	int x = boost::lexical_cast<int>("100");
	long y = boost::lexical_cast<long>("200");
	
	float pai = boost::lexical_cast<float>("3.14159");
	double e = boost::lexical_cast<double>("9.65214");
	double r = boost::lexical_cast<double>("1.414, x", 5); // C 字符串

	std::cout << x << y << pai << e << r << std::endl;

	std::string str = boost::lexical_cast<std::string>(123);
	std::cout << str << std::endl;

	std::cout << boost::lexical_cast<std::string>(0.162342) << std::endl;
	std::cout << boost::lexical_cast<std::string>(0x10) << std::endl;

	return 0;
}
