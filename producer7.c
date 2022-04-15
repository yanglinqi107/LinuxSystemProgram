#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <unistd.h>
#include <errno.h>

#define SHM_KEY 107
#define SEM_KEY 0x107
#define INPUT_PATH "/home/yang/Documents/Cprogram/Linux系统编程学习/producer_input.txt"

union semun
{
    int val;               /* value for SETVAL */
    struct semid_ds *buf;  /* buffer for IPC_STAT & IPC_SET */
    unsigned short *array; /* array for GETALL & SETALL */
    struct seminfo *__buf; /* buffer for IPC_INFO */
    void *__pad;
};

struct BufferPool
{
    char Buffer[5][100]; // 5个缓冲区
    int Index[5];        // 缓冲区状态
    // 0 对应的缓冲区未被生产者使用，可分配但不可消费
    // 非0 为index对应Buffer的数据大小 表示对应的缓冲区已被生产者使用，不可分配但可消费
    int finish;          // 是否结束
    //int fd_out;              //输出文件描述符
    // int fd_in;  //输入文件描述符
    off_t in_pos;    // 输入文件偏移量
    int read_Index;
    int write_Index;
};

//分配资源
int sem_p(int semid)
{
    struct sembuf sem_b;
    sem_b.sem_num = 0;        //信号量编号，单个信号量的编号为0
    sem_b.sem_op = -1;        //信号量操作，-1 为 P操作
    sem_b.sem_flg = SEM_UNDO; //在进程没释放信号量而退出时，系统自动释放该进程中未释放的信号量
    return (semop(semid, &sem_b, 1));
}

//释放资源
int sem_v(int semid)
{
    struct sembuf sem_b;
    sem_b.sem_num = 0;        //信号量编号，单个信号量的编号为0
    sem_b.sem_op = 1;         //信号量操作，1 为 V操作
    sem_b.sem_flg = SEM_UNDO; //在进程没释放信号量而退出时，系统自动释放该进程中未释放的信号量
    return (semop(semid, &sem_b, 1));
}

//删除信号量
int del_sem(int semid)
{
    union semun sem_union;
    return (semctl(semid, 0, IPC_RMID, sem_union));
}

int main()
{
    // 创建共享内存
    int shmid = shmget((key_t)SHM_KEY, sizeof(struct BufferPool), 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("producer : shmget error\n");
        exit(-1);
    }
    //将共享内存连接到进程
    void *shmaddr = shmat(shmid, NULL, 0);
    if (*((int *)shmaddr) == -1)
    {
        perror("producer : shmat error\n");
        exit(-1);
    }
    // 定义执行共享内存的结构体，取数据
    struct BufferPool *shared = (struct BufferPool *)shmaddr;

    // 创建信号量集，信号量数量为1
    int semid;
    union semun sem_union;
    semid = semget(SEM_KEY, 1, 0666 | IPC_CREAT | IPC_EXCL);
    if (semid == -1 && errno == EEXIST)
    {
        semid = semget(SEM_KEY, 1, 0666); //信号量已存在，获取信号量id
    }
    else //信号量刚创建，初始化信号量
    {
        sem_union.val = 1;
        semctl(semid, 0, SETVAL, sem_union);
    }

    // //打开文件，用于输入
    // sem_p(semid);
    // if (shared->fd_in == 0)
    // {
    //     int fd = open(INPUT_PATH, O_RDONLY);
    //     // printf("%d\n", fd);
    //     // sleep(100);
    //     if (fd == -1)
    //     {
    //         perror("producer : open file error\n");
    //         exit(-1);
    //     }
    //     shared->fd_in = dup2(fd, 107);
    //     printf("%d\n", shared->fd_in);
    // }
    // sem_v(semid);

    int fd = open(INPUT_PATH, O_RDONLY);
    if(fd == -1)
    {
        perror("producer : open file error\n");
        exit(-1);
    }

    // printf("%d\n", shared->Index[0]);
    // printf("%d\n", shared->Index[1]);
    // printf("%d\n", shared->Index[2]);
    // printf("%d\n", shared->Index[3]);
    // printf("%d\n", shared->Index[4]);
    // printf("%d\n", shared->finish);

    int index;
    while (1)
    {
        sem_p(semid);
        int index = shared->read_Index;
        if (shared->Index[index] == 0)
        {
            lseek(fd, shared->in_pos, SEEK_SET);
            int size = read(fd, shared->Buffer[index], 20);
            if (size == 0)
            {
                shared->finish = 1;
                sem_v(semid);
                close(fd);
                break;
            }
            off_t currpos = lseek(fd, 0, SEEK_CUR);
            shared->in_pos = currpos;
            shared->Index[index] = size;
            shared->read_Index = (index + 1) % 5;
            //printf("%s", shared->Buffer[index]);
        }
        sem_v(semid);
    }
    // printf("producer over\n");
    //sleep(5);
    if (del_sem(semid) == -1)
    {
        perror("Delete sem error\n");
    }
    if (shmdt(shared) == -1) //解除共享内存映射
    {
        perror(NULL);
    }
    if (shmctl(shmid, IPC_RMID, NULL) == -1) //删除共享内存
    {
        perror("Delete shm error\n");
    }
    return 0;
}