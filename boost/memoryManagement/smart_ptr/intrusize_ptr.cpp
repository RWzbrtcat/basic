#include <iostream>
#include <boost/smart_ptr.hpp>

// 引用计数的类
struct counted_data
{
	int m_count = 0; // 引用计数
	int val = 10; // 储存的数据
};

// 实现 intrusive_ptr 的两个回调函数
// 增加引用计数
void intrusive_ptr_add_ref(counted_data *p)
{
	++p->m_count;
}

// 除了减少引用计数外，还需在引用计数为 0 时，释放资源
void intrusive_ptr_release(counted_data *p)
{
	if (--p->m_count == 0)
	{
		delete p;
	}
}


int main()
{
	typedef boost::intrusive_ptr<counted_data> counted_ptr;

	// 创建智能指针
	counted_ptr p(new counted_data);
	if (p)
	{
		std::cout << "创建指针后: " << p->m_count << std::endl;
	}

	// 使用拷贝构造
	counted_ptr p2(p);
	std::cout << "拷贝构造后: " << p->m_count << std::endl;

	// 弱引用
	counted_ptr weak_p(p.get(), false);
	std::cout << "弱引用: " << p->m_count << std::endl;

	// 重置指针
	p2.reset();
	std::cout << "重置指针后: " << p->m_count << std::endl;

	return 0;
}
