#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{
	boost::posix_time::ptime p = boost::posix_time::from_iso_string("20010203T090909");

	boost::posix_time::minutes min(10);
	boost::posix_time::hours h(1);
	// 以 10 分钟为步长
	for (boost::posix_time::time_iterator t_iter(p, min); t_iter < p + h; ++t_iter)
	{
		std::cout << *t_iter << std::endl;
	}
	return 0;
}
