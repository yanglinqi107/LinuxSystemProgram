#include <unistd.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	int ret;
	fd=open("hole.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd == -1)
    {
        printf("open error\n");
    }
	write(fd,"hello",5);
	ret = lseek(fd, 1024*1024*1024, SEEK_CUR);
	if(ret == -1)
    {
        printf("lseek error\n");
    }
	write(fd,"world",5);
	close(fd);
	return 0;
}
