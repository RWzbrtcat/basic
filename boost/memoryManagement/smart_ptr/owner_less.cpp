#include <iostream>
#include <set>
#include <boost/smart_ptr.hpp>
#include <boost/smart_ptr/owner_less.hpp>  // 需单独包含头文件


int main()
{
	typedef boost::shared_ptr<int> int_ptr; // 共享指针 typedef
	typedef boost::owner_less<int_ptr> int_ptr_less; // 函数对象 typedef

	// 共享指针
	int_ptr p1(new int(10));
	int n = 20;
	// 别名构造
	int_ptr p2(p1, &n);

	// 两者等价
	assert(!int_ptr_less()(p1, p2) && !int_ptr_less()(p2, p1));

	// 关联容器 typedef
	typedef std::set<int_ptr> int_set;

	int_set s;
	s.insert(p1);
	s.insert(p2); // 两者相同，所以不会被插入
	assert(s.size() == 1);
	return 0;
}
