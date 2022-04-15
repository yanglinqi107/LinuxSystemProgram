#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#define READ_SIZE 1024

int main(int argc, char **argv)
{
	if(argc < 2) 
	{
		printf("error\n");
		exit(-1);
	}
	char *sourcePath = argv[1];
	//printf("%s %s\n", argv[1], argv[2]);
	int sfd = open(sourcePath, O_RDONLY);
	if(sfd == -1)
	{
		printf("%s:", sourcePath);
		printf("%s\n", strerror(errno));
		exit(-1);
	}
	
	char *targetPath = argv[2];
	int tfd = -1;
	if(opendir(targetPath) != NULL)
	{
		char *ptr = NULL;
        char *fname = NULL;
		ptr = strrchr(sourcePath, '/');
		if(!ptr)
		{
			ptr = sourcePath;
		}
		else
		{
			fname = (char*)malloc(strlen(ptr));
			memcpy(fname, ptr + 1, strlen(ptr+1));
			ptr = fname;
		}

		int len = strlen(targetPath);
		if(targetPath[len - 1] != '/')
		{
			targetPath = strcat(targetPath, "/");
		}
		targetPath = strcat(targetPath, ptr);
        free(fname);
        ptr = NULL;
        fname = NULL;
		//tfd = open(filename, O_RDWR | O_CREAT | O_EXCL, 0766);
	} 
	tfd = open(targetPath, O_RDWR | O_CREAT | O_EXCL, 0766);
	if(tfd == -1)
	{
		printf("%s:%s\n", targetPath, strerror(errno));
		exit(-1);
	}
	
	char buf[1024];
	int size = -1;
	do{
		size = read(sfd, buf, READ_SIZE);
		if(size == -1)
		{
			printf("%s\n", strerror(errno));
			exit(-1);
		}
		write(tfd, buf, size);
	} while(size == READ_SIZE);
	printf("%s --> %s\n", sourcePath, targetPath);
	close(sfd);
	close(tfd);
	return 0;
}