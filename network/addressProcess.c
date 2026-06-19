#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main()
{
	struct sockaddr_in sa; 
	struct sockaddr_in6 sa6;
	
	// 转换为 二进制存储
	if (inet_pton(AF_INET, "192.168.1.2", &(sa.sin_addr)) <= 0)
	{
		perror("INET4");
		exit(1);
	}

	printf("sa.sinaddr: %u\n", sa.sin_addr);

	if (inet_pton(AF_INET6, "2001:db8:1:1245::9815", &(sa6.sin6_addr)) <= 0)
	{
		perror("INET6");
		exit(1);
	}
	printf("sa6.sinaddr: %u\n", sa6.sin6_addr);

	
	// 转换为 字符串

	char ip4[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN);
	printf("IPv4 Address: %s\n", ip4);

	char ip6[INET6_ADDRSTRLEN];
	inet_ntop(AF_INET6, &(sa6.sin6_addr), ip6, INET6_ADDRSTRLEN);
	printf("IPv6 Address: %s\n", ip6);

	return 0;
}
