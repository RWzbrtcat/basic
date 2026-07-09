#include <iostream>
#include <boost/smart_ptr.hpp>


class node
{
public:
    ~node()
    {
        std::cout << "deleted" << std::endl;
    }
    typedef boost::weak_ptr<node> ptr_type;
    ptr_type next;
};

int main()
{
    auto p1 = boost::make_shared<node>();
    auto p2 = boost::make_shared<node>();

    // 形成循环链表
    p1->next = p2;
    p2->next = p1;
	
    // 每个节点的引用计数都是 1
    std::cout << p1.use_count() << std::endl;
    std::cout << p2.use_count() << std::endl;
    return 0;
}
