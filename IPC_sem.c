#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <time.h>
#include <unistd.h>

union semun
{
    int val;               /* value for SETVAL */
    struct semid_ds *buf;  /* buffer for IPC_STAT & IPC_SET */
    unsigned short *array; /* array for GETALL & SETALL */
    struct seminfo *__buf; /* buffer for IPC_INFO */
    void *__pad;
};

int sem_p(int semid, int semnum); // P操作
int sem_v(int semid, int semnum); // V操作

int main(int argc, char **argv)
{
    int semid, ret;
    union semun arg;
    key_t key = ftok("/tmp", 0x04);
    if (key < 0)
    {
        perror("ftok key error");
        return -1;
    }
    // 1.创建信号量 （创建了三个信号量，实际只用0号信号量）
    semid = semget(key, 3, IPC_CREAT | 0600);
    if (semid == -1)
    {
        perror("create semget error");
        return -1;
    }
    // 2.对0号信号量设置初始值
    arg.val = 1;
    ret = semctl(semid, 0, SETVAL, arg);
    if (ret < 0)
    {
        perror("semctl error");
        semctl(semid, 0, IPC_RMID, arg);
        return -1;
    }
    // 3.打印当前0号信号量的值
    ret = semctl(semid, 0, GETVAL, arg);
    printf("after semctl setval  sem[0].val = %d\n", ret);
    // 4.开始P操作
    printf("P operate begin\n");
    if (sem_p(semid, 0) < 0)
    {
        perror("P operate error");
        return -1;
    }
    printf("P operate end\n");
    ret = semctl(semid, 0, GETVAL, arg);
    printf("after P sem[0].val= %d\n", ret);
    // 5.延时10s		（这个时间段内去执行另一个进程sem2，会在它的P操作那阻塞等待sem执行完V操作）
    sleep(10);
    time_t tNow = time(NULL);
    printf("delay 60S，now time is:%s\n", ctime(&tNow));
    // 6.开始V操作
    printf("V operate begin\n");
    if (sem_v(semid, 0) < 0)
    {
        perror("V operate error");
        return -1;
    }
    printf("V operate end\n");
    ret = semctl(semid, 0, GETVAL, arg);
    printf("after V sem[0].val= %d\n", ret);
    // 7.移除信号量
    sleep(15);
    semctl(semid, 0, IPC_RMID, arg);
    return 0;
}

//对信号量数组semnum编号的信号量做P操作
int sem_p(int semid, int semnum)
{
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = -1;
    op.sem_flg = SEM_UNDO;
    return (semop(semid, &op, 1));
}

//对信号量数组semnum编号的信号量做V操作
int sem_v(int semid, int semnum)
{
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = +1;
    op.sem_flg = SEM_UNDO;
    return (semop(semid, &op, 1));
}