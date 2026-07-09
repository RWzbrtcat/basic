#include <iostream>
#include <boost/smart_ptr.hpp>

class socket_t{
public:
	socket_t() = default;
	~socket_t() = default;
private:
	int fd;
};

socket_t* open_socket()
{
	std::cout << "open socket" << std::endl;
	return new socket_t;
}

void close_socket(socket_t *s)
{
	std::cout << "close socket" << std::endl;
	// 释放资源
	delete s;
}

int main()
{
	socket_t *s = open_socket();
	// 传入删除器
	boost::shared_ptr<socket_t> p(s, close_socket);

	return 0;
}


