#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>

#define READ_SIZE 1024
#define TARGET_PATH "/home/yang/test"

extern void *mycpt(void *arg);

extern void *mydirt(void *arg);
