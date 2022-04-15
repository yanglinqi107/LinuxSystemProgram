#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define FILE_PATH "./test.txt"

int main(void)
{

    int fd;
    if((fd = open(FILE_PATH, O_RDWR | O_CREAT | O_EXCL, 0666)) < 0)
    {
        printf("open error\n"); //test.txt文件存在的话会报错
        exit(-1);
    }
    else
    {
        printf("open success\n");
    }
    printf("fd = %d\n", fd);
    printf("请输入内容到text.txt文件中\n");
    char buf[1024];
    int num = 0;
    if ((num = read(STDIN_FILENO, buf, 200)) == -1)
    {
        printf ("read error");
        exit(-1);
    }
    else
    {
	// 将键盘输入又输出到屏幕上
	write(STDOUT_FILENO, buf, num);

        //将键盘输入 分两次 输出到test.txt文件
        int front = 0;
        if((front = write(fd, buf, 10)) == -1)
        {
            printf("write error\n");
            exit(-1);
        }
        printf("write %d Bytes\n", front);
        if((front = write(fd, buf+10, num-10)) == -1)
        {
            printf("write error\n");
            exit(-1);
        }
            printf("write %d bytes\n", front);
        }
        close(fd);
        return 0;
}
