#include <unistd.h>
#include <stdio.h>

int main()
{
	printf("entering main process--\n");
	if(fork() == 0)
	{
		execl("/bin/ls", "ls", "-l", NULL); 
        //execl后面的代码不会执行，而是运行新的可执行文件的代码
        printf("exiting main process --\n"); //这句代码不会执行
	}
	return 0;
}
