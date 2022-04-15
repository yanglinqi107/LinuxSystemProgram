#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd;
	if((fd = open("./test.txt", O_RDONLY) == -1))
	{
		printf("open error\n");
		exit(-1);
	}
	printf("open success\n");
	printf("fd = %d\n", fd);
	printf("%d\n", STDOUT_FILENO);
	char buf[1024];

	int num = read(fd, buf, 30);
	if(num == -1)
	{
		printf("read error\n");
		exit(-1);
	}
	printf("read %d bytes\n", num);

	num = read(fd, buf, 100);
	if(num == -1)
	{
		printf("read error\n");
		exit(-1);
	}
	printf("read %d bytes\n", num);

	close(fd);
	return 0;
}

