#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	struct stat *buf;
	if(stat("./read测试", buf) == -1)
	{
		printf("stat error\n");
		exit(-1);
	}
	printf("uid = %d\n", buf->st_uid);
	return 0;
}