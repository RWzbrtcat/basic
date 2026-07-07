#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>

template<typename Clock = boost::posix_time::microsec_clock> // 默认使用 microsec_clock
class basic_ptimer{
public:
	basic_ptimer() { restart(); }
	void restart() { _start_time = Clock::local_time(); }

	void elapsed() const 
	{
		std::cout << Clock::local_time() - _start_time << std::endl;
	}

	~basic_ptimer()
	{
		elapsed(); // 析构自动输出流逝时间
	}
private:
	boost::posix_time::ptime _start_time;
};

typedef basic_ptimer<boost::posix_time::microsec_clock> ptimer;
typedef basic_ptimer<boost::posix_time::second_clock> sptimer;

int main()
{
	{
		ptimer pt;
	}
	{
		sptimer spt;
	}
	

	return 0;
}
