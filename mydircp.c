#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define TARGET_PATH "/home/yang/test"
#define MYCP_PATH "/home/yang/Documents/Cprogram/Linux系统编程学习/mycp"
#define MYDIRCP_PATH "/home/yang/Documents/Cprogram/Linux系统编程学习/mydircp"

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
        if(chdir(dirPath) == -1)
        {
            printf("%s is not a directory\n", dirPath);
            exit(-1);
        } 
        dirPath = get_current_dir_name();
    }
    dirPath = strcat(dirPath, "/");

    if (access(TARGET_PATH, F_OK) == -1)
    {
        if (mkdir(TARGET_PATH, 0775) == -1)
        {
            printf("%s\n", strerror(errno));
        }
    }

    DIR *dir = NULL;
    struct stat *currentstat;
    currentstat = (struct stat *)malloc(sizeof(struct stat));
    if ((dir = opendir(dirPath)))
    {
        struct dirent *dp = NULL;
        while ((dp = readdir(dir)))
        {
            if((strcmp(dp->d_name, ".") == 0) || (strcmp(dp->d_name, "..") == 0))
            {
                continue;
            }
            if (stat(dp->d_name, currentstat) == -1)
            {
                printf("get stat error\n");
                continue;
            }
            if (S_ISDIR(currentstat->st_mode))
            {
                pid_t pid_child;
                pid_child = fork();
                if (pid_child < 0)
                {
                    printf("Error occuredon forking.\n");
                }
                else if (pid_child == 0)
                {
                    if (execl(MYDIRCP_PATH, "./mydircp", strcat(dirPath, dp->d_name), NULL) == -1)
                    {
                        printf("mydircp fork error\n");
                        exit(-1);
                    }
                }
            }
            else
            {
                pid_t pid_child;
                pid_child = fork();
                if (pid_child < 0)
                {
                    printf("Error occuredon forking.\n");
                }
                else if (pid_child == 0)
                {
                    if (execl(MYCP_PATH, "./mycp", strcat(dirPath, dp->d_name), TARGET_PATH, NULL) == -1)
                    {
                        printf("mycp fork error\n");
                        exit(-1);
                    }
                }
                // pid_t pid_return;
                //  do
                //  {
                //      pid_return = waitpid(pid_child, NULL, WNOHANG);
                //      sleep(1);
                //      printf("%d\n", pid_child);
                //  } while (pid_return == 0);
            }
            wait(NULL); //阻塞 等待子进程结束
        }
        closedir(dir);
    }
    else if (stat(dirPath, currentstat) == 0) // 如果不是目录
    {
    }
    else
    {
        printf("%s:Not a directory or file\n", dirPath);
    }
    free(currentstat);
    return 0;
}
