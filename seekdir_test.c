#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>

int main()
{
        DIR *dir = opendir("./");
        struct dirent *dent = NULL;

        //先读3个文件
        dent = readdir(dir);
        puts(dent->d_name);
	printf("该文件的offset = %ld\n\n", dent->d_off);

        dent = readdir(dir);
        puts(dent->d_name);
	printf("该文件offset = %ld\n\n", dent->d_off);

	off_t offset = dent->d_off;

        dent = readdir(dir);
        puts(dent->d_name);
	printf("该文件offset = %ld\n\n", dent->d_off);

        seekdir(dir, offset);
	printf("移动到离目录开头偏移%ld\n\n", offset);

        //在读3个文件
        dent = readdir(dir);
        puts(dent->d_name);

        dent = readdir(dir);
        puts(dent->d_name);

        dent = readdir(dir);
        puts(dent->d_name);

	return 0;
}
