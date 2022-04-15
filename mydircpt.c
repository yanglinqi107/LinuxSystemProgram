#define _GNU_SOURCE
#include "mydircpt.h"

int main(int argc, char **argv)
{
    char *dirPath = NULL;
    if (argc == 1)
    {
        dirPath = get_current_dir_name();
    }
    else
    {
        dirPath = argv[1];
        if (chdir(dirPath) == -1)
        {
            printf("A %s : Not a directory\n", dirPath);
            exit(-1);
        }
        dirPath = get_current_dir_name();
    }
    dirPath = strcat(dirPath, "/");

    if (access(TARGET_PATH, F_OK) == -1)
    {
        if (mkdir(TARGET_PATH, 0775) == -1)
        {
            printf("B %s\n", strerror(errno));
        }
    }

    pthread_t child;
    if (pthread_create(&child, NULL, mydirt, dirPath) != 0)
    {
        printf("C %s\n", strerror(errno));
        exit(-1);
    }
    pthread_join(child, NULL);
    // if(pthread_detach(child) != 0)
    // {
    //     printf("fjoew\n");
    // }
    return 0;
}
