#include <stdio.h>
#include <stdlib.h>

int i, j ,k;

void func1(int status, void *arg)
{
	printf("func1 exit status is %d\n", status);
	printf("func1 arg is %d\n", *((int*)arg));
}

void func2(int status, void *arg)
{
	printf("func2 exit status is %d\n", status);
	printf("func2 arg is %d\n", *((int*)arg));
}

void func3(int status, void *arg)
{
	printf("func3 exit status is %d\n", status);
	printf("func3 arg is %d\n", *((int*)arg));
}


int main(int *argc, char **argv)
{
	i = 3;
	on_exit(func1, (void*)&i);
	j = 4;
	on_exit(func2, (void*)&j);
	k = 5;
	on_exit(func3, (void*)&k);
	return 1;
}