#include <stdio.h>
#include <unistd.h>

#define MAX_SIZE 255

int main()
{
	char path[MAX_SIZE];
	getcwd(path, sizeof(path));
	puts(path);
	return 0;
}
