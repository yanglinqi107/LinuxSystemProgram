#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid_child, pid_return;
    pid_child = fork();
    if (pid_child < 0)
    {
        printf("Error occuredon forking.\n");
    }
    else if (pid_child == 0)
    {
        sleep(10);
        exit(0);
    }
    do
    {
        pid_return = waitpid(pid_child, NULL, WNOHANG);
        if (pid_return == 0)
        {
            printf("No child exited\n");
            sleep(1);
        }
    } while (pid_return == 0);
    if (pid_return == pid_child)
    {
        printf("successfullyget child %d\n", pid_return);
    }
    else
    {
        printf("some error occured\n");
    }
    return 0;
}
