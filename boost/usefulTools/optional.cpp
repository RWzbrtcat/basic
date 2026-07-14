#include <iostream>
#include <vector>
#include <cmath>
#include <boost/optional.hpp>

// 计算倒数
boost::optional<double> calc(int x)
{
	return boost::optional<double>(x != 0, 1.0 / x); // 条件构造函数
}

// 计算实数的平方根
boost::optional<double> sqrt_op(double x)
{
	return boost::optional<double>(x >= 0, std::sqrt(x));
}


int main()
{
	// 未初始化的 optional 对象
	boost::optional<int> op0;
	// 使用 none 赋予其未初始化值
	boost::optional<int> op1(boost::none);

	if (!op0)
	{
		std::cout << "op0 未被初始化" << std::endl;
	}

	if (op0 == op1)
	{
		std::cout << "op0 和 op1 相同" << std::endl;
	}

	// 获取默认值 255
	std::cout << "default: " <<  op0.value_or(255) << std::endl;
	// 使用函数对象
	std::cout << op0.value_or_eval([](){ return 1024; }) << std::endl;

	// 初始化为字符串 test
	boost::optional<std::string> ops("test");
	// 用解引用操作符获取值
	std::cout << "ops: " << *ops << std::endl;
	
	// 就地创建一个字符串
	ops.emplace("optional", 3);
	// 只使用了前三个字符
	std::cout << "ops(emplace): " << *ops << std::endl;

	// 容器
	std::vector<int> v(10);
	boost::optional<std::vector<int>&> opv(v);

	// 使用箭头操作符操纵容器
	opv->push_back(5);
	std::cout << "v.size(): " << opv->size() << std::endl;


	// 解决一些无效值的问题
	boost::optional<double> d = calc(10);
	if (d)
	{
		std::cout << *d << std::endl;
	}

	d = sqrt_op(-10);
	if (!d)
	{
		std::cout << "no result" << std::endl;
	}

	return 0;
}
