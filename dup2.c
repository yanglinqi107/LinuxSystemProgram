#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>

int main(int argc, char *argv[])
{
    int shmid = shmget((key_t)1234, sizeof(int), 0666 | IPC_CREAT);
    void *shmaddr = shmat(shmid, NULL, 0);

    int fd = *((int *)shmaddr);

    printf("%d\n", fd);

    char buf[100];
    read(fd, buf, 50);
    printf("%s", buf);

    read(fd, buf, 50);
    printf("%s", buf);


    return 0;
}