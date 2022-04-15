#define _GNU_SOURCE
#include "mydircpt.h"

void *mydirt(void *arg)
{
    char *dirPath = (char *)arg;
    chdir(dirPath);
    dirPath = get_current_dir_name();
    DIR *dir = NULL;
    struct stat *currentstat;
    currentstat = (struct stat *)malloc(sizeof(struct stat));
    if ((dir = opendir(dirPath))) // 打开目录
    {
        struct dirent *dp = NULL;
        while ((dp = readdir(dir)))
        {
            if ((strcmp(dp->d_name, ".") == 0) || (strcmp(dp->d_name, "..") == 0))
            {
                continue;
            }
            if (stat(dp->d_name, currentstat) == -1)
            {
                printf("D : %s \n", dirPath);
                printf("%s \n", get_current_dir_name());
                printf("%s : get stat error  %s \n", dp->d_name, strerror(errno));
                continue;
            }
            pthread_t thread_child;
            char *tmp = (char *)malloc(strlen(dirPath) + strlen(dp->d_name) + 2);
            strcpy(tmp, dirPath);
            strcat(tmp, "/");
            strcat(tmp, dp->d_name);

            if (S_ISDIR(currentstat->st_mode)) // 判断是不是目录
            {
                if (pthread_create(&thread_child, NULL, mydirt, tmp) != 0)
                {
                    printf("E : Error pthread create.\n");
                    pthread_exit(NULL);
                }
            }
            else // 文件
            {
                if (pthread_create(&thread_child, NULL, mycpt, tmp) != 0)
                {
                    printf("F : Error pthread create.\n");
                    pthread_exit(NULL);
                }
            }
            pthread_join(thread_child, NULL); //阻塞 等待线程结束
            free(tmp);
            chdir(dirPath);
            // if (pthread_detach(thread_child) != 0)
            // {
            //     printf("pthread_detach error\n");
            // }
        }
        closedir(dir);
        //sleep(10);
    }
    else
    {
        printf("G %s : Not a directory\n", dirPath);
    }
    pthread_exit(NULL);
}
