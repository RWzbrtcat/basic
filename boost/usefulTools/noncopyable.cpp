#include <iostream>
#include <boost/noncopyable.hpp>


class notCopy : boost::noncopyable
{

};


int main(){
	notCopy nc1;
	notCopy nc2(nc1); // 企图拷贝构造
	notCopy nc3;
	nc3 = nc1; // 企图拷贝赋值	
	return 0;
}
