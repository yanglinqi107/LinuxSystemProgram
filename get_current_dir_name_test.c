#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>

int main()
{
        char *path;
	path = get_current_dir_name();
        puts(path);
        return 0;
}
