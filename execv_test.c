#include <stdio.h>
#include <unistd.h>

int main()
{
    int ret;
    char *argv[] = {"ls", "-l", NULL};
    printf("entering main process --\n");
    if(fork() == 0)
    {
        ret = execv("/bin/ls", argv);
        if(ret == -1)
        {
            perror("execv error\n");
        }
        printf("exiting main process --\n");
    }
    return 0;
}
