#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>

struct BufferPool
{
    char Buffer[5][100]; // 5 个缓冲区
    int Index[5];	//缓冲区状态
    // 0 表示 对应的缓冲区未被生产者使用，可生产但不可消费
    // 1 表示 对应的缓冲区已被生产者使用，不可生产但可消费
};

int main()
{
    int running = 1;
    void *shm = NULL;
    struct BufferPool *shared;
    char buffer[100];
    int shmid;
	int index;
    shmid = shmget((key_t)1234, sizeof(struct BufferPool), 0666 | IPC_CREAT);
    if(shmid == -1)
    {
        exit(EXIT_FAILURE);
    }
    shm = shmat(shmid, (void*)0, 0);
    if(*((int*)shm) == -1)
    {
        exit(EXIT_FAILURE);
    }
    printf("Memory attached at %X\n", (int*)shm);
    shared = (struct BufferPool*)shm;
    while(running)
    {
        index = 0;
        if(shared->Index[index] == 1)
        {
            sleep(1);
            ++index;
        }
        else
        {
            printf("Enter some text:");
            fgets(buffer, 100, stdin);
            strncpy(shared->Buffer[index], buffer, 100);
            shared->Index[index] = 1;
            if(strncmp(buffer, "end", 3) == 0)
            {
                running = 0;
            }
        }
    }
    if(shmdt(shm) == -1)
    {
        exit(EXIT_FAILURE);
    }
    if(shmctl(shmid, IPC_RMID, 0) == -1)
    {
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}