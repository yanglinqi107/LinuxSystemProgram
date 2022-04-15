#define _GNU_SOURCE
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>

void print_type(mode_t st_mode);

void print_perm(mode_t st_mode);

void print_link(nlink_t st_nlink);

void print_usrname(uid_t st_uid);

void print_grname(gid_t st_gid);

void print_size(off_t size);

void print_time(time_t mtime);

void print_filename(char *fname);

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
		chdir(dirPath);
	}

	DIR *dir = NULL;
	struct stat *currentstat;
	currentstat = (struct stat *)malloc(sizeof(struct stat));
	if ((dir = opendir(dirPath)))
	{
		struct dirent *dp = NULL;

		while ((dp = readdir(dir)))
		{
			// printf("%s\n", dirent->d_name);
			if (stat(dp->d_name, currentstat) == -1)
			{
				printf("get stat error\n");
				continue;
			}
			print_type(currentstat->st_mode);
			print_perm(currentstat->st_mode);
			print_link(currentstat->st_nlink);
			print_usrname(currentstat->st_uid);
			print_grname(currentstat->st_gid);
			print_size(currentstat->st_size);
			print_time(currentstat->st_mtime);
			print_filename(dp->d_name);
		}
		closedir(dir);
	}
	else if (stat(dirPath, currentstat) == 0)
	{
		print_type(currentstat->st_mode);
		print_perm(currentstat->st_mode);
		print_link(currentstat->st_nlink);
		print_usrname(currentstat->st_uid);
		print_grname(currentstat->st_gid);
		print_size(currentstat->st_size);
		print_time(currentstat->st_mtime);
		print_filename(dirPath);
	}
	else
	{
		printf("%s:Not a directory or file\n", dirPath);
	}
	free(currentstat);
	return 0;
}

void print_type(mode_t st_mode)
{
	if (S_ISREG(st_mode))
	{
		printf("-");
	}
	else if (S_ISDIR(st_mode))
	{
		printf("d");
	}
	else if (S_ISCHR(st_mode))
	{
		printf("c");
	}
	else if (S_ISBLK(st_mode))
	{
		printf("b");
	}
	else if (S_ISFIFO(st_mode))
	{
		printf("p");
	}
	else if (S_ISLNK(st_mode))
	{
		printf("l");
	}
	else if (S_ISSOCK(st_mode))
	{
		printf("s");
	}
}

void print_perm(mode_t st_mode)
{
	//文件所有者
	if ((st_mode & S_IRUSR) == S_IRUSR)
	{
		printf("r");
	}
	else
	{
		printf("-");
	}
	if ((st_mode & S_IWUSR) == S_IWUSR)
	{
		printf("w");
	}
	else
	{
		printf("-");
	}
	if ((st_mode & S_IXUSR) == S_IXUSR)
	{
		printf("x");
	}
	else
	{
		printf("-");
	}
	//同组用户
	if ((st_mode & S_IRGRP) == S_IRGRP)
	{
		printf("r");
	}
	else
	{
		printf("-");
	}
	if ((st_mode & S_IWGRP) == S_IWGRP)
	{
		printf("w");
	}
	else
	{
		printf("-");
	}
	if ((st_mode & S_IXGRP) == S_IXGRP)
	{
		printf("x");
	}
	else
	{
		printf("-");
	}
	//其他用户
	if ((st_mode & S_IROTH) == S_IROTH)
	{
		printf("r");
	}
	else
	{
		printf("-");
	}
	if ((st_mode & S_IWOTH) == S_IWOTH)
	{
		printf("w");
	}
	else
	{
		printf("-");
	}
	if ((st_mode & S_IXOTH) == S_IXOTH)
	{
		printf("x");
	}
	else
	{
		printf("-");
	}

	printf("\t");
}

void print_link(nlink_t st_nlink)
{
	printf("%ld\t", st_nlink);
}

void print_usrname(uid_t st_uid)
{
	struct passwd *usr = getpwuid(st_uid);
	printf("%s\t", usr->pw_name);
}

void print_grname(gid_t st_gid)
{
	struct group *grp = getgrgid(st_gid);
	printf("%s\t", grp->gr_name);
}

void print_size(off_t size)
{
	printf("%ld\t", size);
}

void print_time(time_t mtime)
{
	// char *time = ctime(&mtime); //返回的字符串 如： Sun Apr 10 16:34:37 2022\n
	// printf("%s", time);

	struct tm *time = localtime(&mtime);
	char *months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sept", "Oct", "Nov"};
	printf("%s %2d %02d:%02d\t", months[time->tm_mon], time->tm_mday, time->tm_hour, time->tm_min);
}

void print_filename(char* fname)
{
	printf("%s\n", fname);
}
