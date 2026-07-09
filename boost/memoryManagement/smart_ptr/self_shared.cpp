#include <iostream>
#include <boost/smart_ptr.hpp>


class self_shared : public boost::enable_shared_from_this<self_shared>
{
public:
	self_shared(int n) : x(n){}
	int x;
	void print()
	{
		std::cout << "self_shared: " << x << std::endl;
	}
};


int main()
{
	auto sp = boost::make_shared<self_shared>(313);
	sp->print();

	auto p = sp->shared_from_this();
	p->x = 100;
	p->print();
	return 0;
}
