#include <stdio.h>
void* test()
{
    int a = 3;
    int *i;
    i = &a;
    printf("%p\n", i);
    //void *v = (void*)i;
    static int *b;
    return b;
}

int main(void) {
    test();
    return 0;
}
