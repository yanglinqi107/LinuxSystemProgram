#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    FILE *fp;
    int fd;
    if ((fp = fopen("hello.txt", "w+")) == NULL) 
    {
        printf("fopen file error\n");
        return 0;
    }
    fprintf(fp, "hello word\n");
    fclose(fp);

    if((fd = open("hello.txt", O_RDWR)) == -1) 
    {
        printf("open file fail\n");
        return 0;
    }

    if((fp = fdopen(fd, "a+")) == NULL) 
    {
        printf("fdopen open\n");
        return 0;
    }
    fprintf(fp, "linux c program\n");
    fclose(fp);
    return 0;
}
