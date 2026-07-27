
#define BOOST_TEST_MAIN  // 定义主测试套件
#include <boost/test/unit_test.hpp>

#include <boost/smart_ptr.hpp>
#include <iostream>

// 测试套件开始（可定义/不定义，因为已经定义了主测试套件）
BOOST_AUTO_TEST_SUITE(s_smart_ptr)

BOOST_AUTO_TEST_CASE(t_scoped_ptr)
{
	boost::scoped_ptr<int> p(new int(874));
	BOOST_CHECK(p); // p 不是空指针
	BOOST_CHECK_EQUAL(*p, 874); // 是否相等

	p.reset();
	BOOST_CHECK(!p);  // 空指针
}

BOOST_AUTO_TEST_CASE(t_shared_ptr)
{
	auto p = boost::make_shared<int>(100);

	BOOST_CHECK(p);
	BOOST_CHECK_EQUAL(*p, 100);
	BOOST_CHECK_EQUAL(p.use_count(), 1); // 引用计数为 1

	auto p2 = p;
	BOOST_CHECK_EQUAL(p2, p);
	BOOST_CHECK_EQUAL(p2.use_count(), 2); // 引用计数为 2

	*p2 = 255;
	BOOST_CHECK_EQUAL(*p, 255);
	BOOST_CHECK_GT(*p, 200);
}

BOOST_AUTO_TEST_SUITE_END()
