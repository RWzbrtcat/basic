#include <iostream>
#include <boost/smart_ptr.hpp>
#include <boost/core/lightweight_test.hpp>

int main()
{
	auto p = boost::make_shared<int>(10);

	// 测试解引用
	BOOST_TEST(*p == 10);
	// 测试唯一性
	BOOST_TEST(p.unique());
	// 测试指针是否为空
	BOOST_TEST_NOT(!p);

	// 相等测试
	BOOST_TEST_EQ(p.use_count(), 1);
	// 不等测试
	BOOST_TEST_NE(*p, 20);

	p.reset();
	BOOST_TEST(!p);
	
	// 测试抛出异常，失败
	// BOOST_TEST_THROWS(*p, std::runtime_error);
	// 输出错误消息
	// BOOST_ERROR("error accured!!");


	return boost::report_errors();
}
