#include <iostream>
#include <boost/logic/tribool.hpp>

// 自定义 tribool 的输出运算符
std::ostream& operator<<(std::ostream& os, const boost::logic::tribool& tb) {
    if (boost::logic::indeterminate(tb)) {
        os << "indeterminate";
    } else {
        os << (tb ? "true" : "false");
    }
    return os;
}

int main()
{
	boost::logic::tribool tb(true); // 值为 true 的 tribool
	boost::logic::tribool tb2(!tb); // 值为 false

	if (tb)
	{
		std::cout << "tb: true" << std::endl; 
	}

	tb2 = boost::logic::indeterminate;
	std::cout << tb2 << std::endl;

	// 与 indeterminate 的比较无意义
	if (tb2 == boost::logic::indeterminate)
	{
		std::cout << "不会进入该语句" << std::endl;
	}

	if (boost::logic::indeterminate(tb2))
	{
		std::cout << "indeterminate" << std::endl;
	}

	std::cout << (tb2 || true) << std::endl;
	std::cout << (tb2 && false) << std::endl;

	return 0;
}
