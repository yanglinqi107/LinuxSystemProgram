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
    int shmid = shmget((key_t)1234, sizeof(int), 0666| IPC_CREAT);
    void *shmaddr = shmat(shmid, NULL, 0);
    int fd = open("producer_input.txt", O_RDONLY);
    if (fd < 0)
    {
        printf("open error!\n");
        return 0;
    }
    char buf[100];
    read(fd, buf, 50);
    printf("%s", buf);

    int i_fd = dup(fd);
    printf("%d  %d \n", fd, i_fd);
    shmaddr = (void *)&i_fd;
    printf("%d\n", *((int*)shmaddr));

    read(fd, buf, 50);
    printf("%s", buf);

    //sleep();

    return 0;
}