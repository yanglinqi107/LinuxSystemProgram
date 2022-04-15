#include "mydircpt.h"

void *mycpt(void *arg)
{
    char *sourcePath = (char *)arg;
    //printf("mycpt %s\n", sourcePath);
    int sfd = open(sourcePath, O_RDONLY);
    if (sfd == -1)
    {
        printf("H %s:", sourcePath);
        printf("%s\n", strerror(errno));
        pthread_exit(NULL);
    }

    // char *targetPath = TARGET_PATH;
    char *targetPath = (char *)malloc(strlen(TARGET_PATH) + 2);
    strcpy(targetPath, TARGET_PATH);
    int tfd = -1;
    if (opendir(targetPath) != NULL)
    {
        char *ptr = NULL;
        char *fname = NULL;
        ptr = strrchr(sourcePath, '/');
        if (!ptr)
        {
            ptr = sourcePath;
        }
        else
        {
            fname = (char *)malloc(strlen(ptr));
            memcpy(fname, ptr + 1, strlen(ptr + 1));
            ptr = fname;
        }

        int len = strlen(targetPath);
        if (targetPath[len - 1] != '/')
        {
            targetPath = strcat(targetPath, "/");
        }
        targetPath = (char*)realloc(targetPath, strlen(targetPath) + strlen(ptr) + 1);
        targetPath = strcat(targetPath, ptr);
        free(fname);
        ptr = NULL;
        fname = NULL;
        // tfd = open(filename, O_RDWR | O_CREAT | O_EXCL, 0766);
    }
    tfd = open(targetPath, O_RDWR | O_CREAT | O_EXCL, 0766);
    if (tfd == -1)
    {
        printf("I %s:%s\n", targetPath, strerror(errno));
        pthread_exit(NULL);
    }

    char buf[1024];
    int size = -1;
    do
    {
        size = read(sfd, buf, READ_SIZE);
        if (size == -1)
        {
            printf("J %s\n", strerror(errno));
            pthread_exit(NULL);
        }
        write(tfd, buf, size);
    } while (size == READ_SIZE);
    printf("%s --> %s\n", sourcePath, targetPath);
    close(sfd);
    close(tfd);
    pthread_exit(NULL);
}