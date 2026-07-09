#include <boost/smart_ptr.hpp>

class sample{
private:
	class impl; // 不完整的内部类声明
	boost::shared_ptr<impl> p;
public:
	sample();
	void print();	
};
