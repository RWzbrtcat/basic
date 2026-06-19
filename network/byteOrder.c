#include <stdio.h>

int verifyByteOrder()
{
	int i = 0; // 0x00000001 
	char *p = (char *)&i;
	// 如果读取到的第一个字节为1，则为小端，否则为大端
	return *p == 0;
}


int main()
{
	if (verifyByteOrder() == 1)
	{
		printf("Little Endian\n");
	}
	else
	{
		printf("Big Endian\n");
	}

	return 0;
}
