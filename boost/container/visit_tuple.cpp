#include <iostream>
#include <boost/tuple/tuple.hpp>


template<typename T>
struct max_visitor
{
	T* tmp; // 最大值
	max_visitor(T *t): tmp(t) {}

	typedef void result_type;

	result_type operator()(const T &t)
	{
		*tmp = *tmp < t ? t :*tmp;
	}
};

// 主模板
template<typename Visitor, typename Tuple>
typename Visitor::result_type
visit_tuple(Visitor v, const Tuple &t)
{
	v(t.get_head());
	return visit_tuple(v, t.get_tail()); 
}

template<>
void visit_tuple(max_visitor<double>, const boost::tuples::null_type&) {}

int main()
{
	boost::tuple<int, long, float, double> t(100, 5, 3.14, 314.15);
	
	// 设置初始值
	double *max_value = new double(t.get_head());
	// 创建访问者函数对象
	max_visitor<double> mv(max_value);
	// 访问 tuple
	visit_tuple(mv, t);

	std::cout << *max_value << std::endl;

	return 0;
}
