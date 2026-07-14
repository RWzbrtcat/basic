#include <iostream>
#include <stack>
#include <boost/assign.hpp>
using namespace boost::assign;

int main()
{
	std::stack<int> st = (list_of(1), 2, 3).to_adapter();
	st += 4, 5, 6;
	while (!st.empty())
	{
		std::cout << st.top() << " ";
		st.pop();
	}
	std::cout << std::endl;
	
	std::queue<std::string> que = (list_of("china")("us")("uk")).repeat(2, "russia").to_adapter();
	push(que)("germany");
	while (!que.empty())
	{
		std::cout << que.front() << " ";
		que.pop();
	}
	std::cout << std::endl;
	return 0;
}
