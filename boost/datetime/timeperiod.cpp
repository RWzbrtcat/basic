#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


int main()
{
	boost::gregorian::date d(2011, 11, 11);
	boost::posix_time::time_duration td(2, 2, 2);

	boost::posix_time::ptime p1(d, td);
	boost::posix_time::ptime p2(d, td + boost::posix_time::hours(20));

	boost::posix_time::time_period tp1(p1, p2);

	std::cout << "begin: " << tp1.begin() << std::endl;
	std::cout << "end: " << tp1.end() << std::endl;

	return 0;
}
