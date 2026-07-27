#include <iostream>
#include <boost/test/included/unit_test.hpp>
#include <boost/assign.hpp>
#include <vector>

// 全局测试夹具类

struct global_fixture
{
	global_fixture() { std::cout << "global setup\n"; }
	~global_fixture() { std::cout << "global teardown\n"; }
};

// 定义全局测试夹具类
BOOST_TEST_GLOBAL_FIXTURE(global_fixture);
// global_fixture gf;

// 测试套件夹具类
struct assign_fixture
{
	assign_fixture() { std::cout << "suit setup\n"; }
	~assign_fixture() { std::cout << "suit teardown\n"; }

	// 所有测试用例都可用的成员变量
	std::vector<int> v;
};

// 定义测试套件级别的夹具
BOOST_FIXTURE_TEST_SUITE( s_assign, assign_fixture )

// 测试 += 操作符
BOOST_AUTO_TEST_CASE(t_assign1)
{
	using namespace boost::assign;
	v += 1, 2, 3, 4;
	BOOST_CHECK_EQUAL(v.size(), 4);
	BOOST_CHECK_EQUAL(v[2], 3);
}

// 测试 push_back 
BOOST_AUTO_TEST_CASE(t_assign2)
{
	boost::assign::push_back(v)(10)(20)(30);

	BOOST_CHECK_EQUAL(v.empty(), false);
	BOOST_CHECK_EQUAL(v.size(), 3); 
}

// 测试套件结束
BOOST_AUTO_TEST_SUITE_END()

// 添加初始化函数
boost::unit_test::test_suite* init_unit_test_suite(int argc, char* argv[])
{
    // 如果需要自定义初始化，可以在这里添加
    // 返回 nullptr 表示使用自动注册的测试
    return nullptr;
}
