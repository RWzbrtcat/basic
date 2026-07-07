#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{
	boost::gregorian::date d(2002, 2, 2);
	boost::posix_time::time_duration td(1, 2, 3);
	boost::posix_time::ptime p(d, td);
	tm t = to_tm(p);
	std::cout << t.tm_year << std::endl;

	boost::posix_time::ptime p2 = boost::posix_time::ptime_from_tm(t);
	std::cout << p2 << std::endl;
	return 0;
}
