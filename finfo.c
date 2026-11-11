/************************************
* Lab 9 SysProg 111
* @author Joey Hernandez
* @date 10/29/2026
* @file finfo.c
* compile: Makefile
************************************/

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

// check file type (similar to pinfo *scheduler_name)
// dont use switch since S_IS*** checks file type natively, use if and check all types
const char *file_type(mode_t mode)
{
    if (S_ISREG(mode))
        return "Regular file";

    if (S_ISDIR(mode))
        return "Directory";

    if (S_ISCHR(mode))
        return "Character device";

    if (S_ISBLK(mode))
        return "Block device";

    if (S_ISFIFO(mode))
        return "FIFO/Pipe";

    if (S_ISLNK(mode))
        return "Symbolic link";

    if (S_ISSOCK(mode))
        return "Socket";

    return "Unknown file type";
}

// print file permissions of user group and others (ie read, write, -) using I(w/x/r)USR, etc
void print_permissions(mode_t mode)
{

    printf("Permissions: ");
    // mode & S_I**** checks if the r/w/x bit is set in mode, if so it prints the corresponding letter, otherwise a '-'
    printf("%c", (mode & S_IRUSR) ? 'r' : '-');
    printf("%c", (mode & S_IWUSR) ? 'w' : '-');
    printf("%c", (mode & S_IXUSR) ? 'x' : '-');

    printf("%c", (mode & S_IRGRP) ? 'r' : '-');
    printf("%c", (mode & S_IWGRP) ? 'w' : '-');
    printf("%c", (mode & S_IXGRP) ? 'x' : '-');

    printf("%c", (mode & S_IROTH) ? 'r' : '-');
    printf("%c", (mode & S_IWOTH) ? 'w' : '-');
    printf("%c", (mode & S_IXOTH) ? 'x' : '-');

    printf("\n"); // go to newline after putting all char's on the same line
}

int main(int argc, char* argv[])
{
    struct stat file_info;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }

    // Retrieve file information
    if (stat(argv[1], &file_info) == -1) {
        perror("stat");
        return 1;
    }

    // print file info (name, type, permissions, uid, size)
    printf("File: %s\n", argv[1]);
    printf("File type: %s\n", file_type(file_info.st_mode));
    print_permissions(file_info.st_mode);
    printf("Owner UID: %u\n", file_info.st_uid);
    printf("File size: %lld bytes\n", (long long)file_info.st_size);

    // convert modification time to readable date
    char time_string[100];
    struct tm *modification_time = localtime(&file_info.st_mtime);
    if (modification_time != NULL) {
        strftime(time_string, sizeof(time_string),
                 "%Y-%m-%d %H:%M:%S", modification_time);

        printf("Last modified: %s\n", time_string);
    }
    return 0;
}
