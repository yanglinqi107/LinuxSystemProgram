#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//extern errorno;

int main(int argc,char *argv[])
{
	int i = open("/usr/src/s.t",0);
	perror(argv[0]);
	printf("%s", strerror(errno));
	printf("\n");
	return 0;
}