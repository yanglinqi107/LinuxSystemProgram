#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM 6

// static int chopstick[NUM];

pthread_mutex_t chopstick_lock[NUM];

void *philosopher(void *arg); //线程例程

int takechopstick(int number);
int putchopstick(int number);

int main()
{
    srand((unsigned int)time(NULL));

    pthread_t pt[NUM];
    char *p = (char *)malloc(NUM);
    char tmp = 'A';
    for (int i = 0; i < NUM; ++i)
    {
        p[i] = tmp + i;
        pthread_create(&pt[i], NULL, philosopher, &p[i]);
        pthread_mutex_init(&chopstick_lock[i], NULL);
        // chopstick[i] = 0;
    }

    for (int i = 0; i < NUM; ++i)
    {
        pthread_join(pt[i], NULL);
    }
    free(p);
    return 0;
}

void *philosopher(void *arg) //线程例程
{
    char name = *((char *)arg);
    int number = name - 'A';
    while (1)
    {
        printf("philosopher %c is thinking\n", name);
        sleep(rand() % 3);
        // pthread_mutex_lock(&chopstick_lock);
        if (!takechopstick(number))
        {
            continue;
        }
        printf("philosopher %c fetches chopstick %d\n", name, number);
        sleep(1);
        if (!takechopstick((number + 1) % NUM))
        {
            putchopstick(number);
            printf("philosopher %c failed and release chopstick %d\n", name, number);
            continue;
        }
        printf("philosopher %c fetches chopstick %d\n", name, (number + 1) % NUM);
        printf("philosopher %c is eating\n", name);
        sleep(rand() % 3);
        putchopstick(number);
        printf("philosopher %c release chopstick %d\n", name, number);
        putchopstick((number + 1) % NUM);
        printf("philosopher %c release chopstick %d\n", name, (number + 1) % NUM);
        // pthread_mutex_unlock(&chopstick_lock);
    }
}

int takechopstick(int number)
{
    if (pthread_mutex_trylock(&chopstick_lock[number]) != 0)
    {
        return 0;
    }
    return 1;
}

int putchopstick(int number)
{
    pthread_mutex_unlock(&chopstick_lock[number]);
}