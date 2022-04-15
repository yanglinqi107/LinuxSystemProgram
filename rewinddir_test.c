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
	dent = readdir(dir);
        puts(dent->d_name);
	dent = readdir(dir);
        puts(dent->d_name);
	//设置会开头
	rewinddir(dir);
	//在读3个文件
	dent = readdir(dir);
        puts(dent->d_name);
        dent = readdir(dir);
        puts(dent->d_name);
        dent = readdir(dir);
        puts(dent->d_name);

	return 0;
}
