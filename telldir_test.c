#define _GNU_SOURCE
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
        DIR *dir = opendir("./");
        struct dirent *dent = NULL;
	int i = 0;
        while(i++ < 5)
        {
		dent = readdir(dir);
                puts(dent->d_name);
		printf("dirent->d_off = %ld\n", dent->d_off);
		off_t offset = telldir(dir);
		printf("telldir = %ld\n\n", offset);
        }
        return 0;
}
