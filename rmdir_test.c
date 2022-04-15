#include <unistd.h>
#include <stdio.h>

int main()
{
    if(rmdir("./mulu") == -1)
    {
	printf("rmdir error\n");
    }
    return 0;
}
