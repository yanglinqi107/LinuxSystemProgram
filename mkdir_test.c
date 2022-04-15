#include <stdio.h>
#include <sys/stat.h>
#define PATH "/home/yang/Documents/Cprogram/Linux系统编程学习/mulu"

int main()
{
	//umask(0);
	if(mkdir(PATH, S_IRWXU | S_IRGRP | S_IROTH) == -1)
	{
		printf("mkdir error\n");
	}
	return 0;
}
