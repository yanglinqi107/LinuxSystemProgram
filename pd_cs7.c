#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PRODUCER "/home/yang/Documents/Cprogram/Linux系统编程学习/producer7"
#define CONSUMER "/home/yang/Documents/Cprogram/Linux系统编程学习/consumer7"

int main()
{
    pid_t producer[3];
    pid_t consumer[3];

    for(int i = 0; i < 3; ++i)
    {
        producer[i] = fork();
        if(producer[i] == -1)
        {
            perror("producer fork error\n");
        }
        else if(producer[i] == 0)
        {
            execl(PRODUCER, "./producer7", NULL);
        }
        consumer[i] = fork();
        if(consumer[i] == -1)
        {
            perror("consumer fork error\n");
        }
        else if(consumer[i] == 0)
        {
            execl(CONSUMER, "./consumer7", NULL);
        }
    }
    return 0;
}