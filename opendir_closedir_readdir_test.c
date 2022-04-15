#define _GNU_SOURCE
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_SIZE 255
#define path "/home/yang/Documents/Cprogram"

int main()
{
	DIR *dir = opendir(path);
	char dir1[MAX_SIZE];
	getcwd(dir1, sizeof(dir1));
	puts(dir1);
	char *dir2 = get_current_dir_name();
	puts(dir2);
	struct dirent *dent = NULL;
	while((dent = readdir(dir)) != NULL)
	{
		puts(dent->d_name);
	}
	return 0;
}
