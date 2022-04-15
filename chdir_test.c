#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#define PATH "/home/yang"

int main()
{
    if(chdir("..") == -1)
    {
	puts("chdir error");
    }
    char *nowdir = get_current_dir_name();
    puts(nowdir);

    if(chdir(PATH) == -1)
    {
        puts("chdir error");
    }
    nowdir = get_current_dir_name();
    puts(nowdir);

    return 0;
}
