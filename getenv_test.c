#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char *path = getenv("PATH");
	puts(path);
	return 0;
}