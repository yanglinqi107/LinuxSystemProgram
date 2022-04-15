#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

void *childthread()
{
    int i;
    for(i = 0; i < 10; ++i)
    {
        printf("childthread message\n");
        sleep(2); // 单位是s
        pthread_exit(NULL);
    }
}

int main()
{
    pthread_t tid;
    printf("create childthread\n");
    pthread_create(&tid, NULL, (void*)childthread, NULL);
    pthread_join(tid, NULL);
    printf("childthread exit\n");
    return 0;
}
