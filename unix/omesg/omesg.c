// @file omesg.c
// @desc linux command mesg
//       修改当前tty的其他用户可写权限
//       与mesg不同的是mesg只修改用户组可写权限
// @auth hatlonely (hatlonely@gmail.com)
// @date 2014-4-16

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc > 2) {
        printf("usage: omesg [y/n]");
        return -1;
    }

    char cmd[1024];
    if (argc == 1) {
        struct stat buf;
        stat(ttyname(STDIN_FILENO), &buf);
        if ((buf.st_mode & S_IWOTH) && (buf.st_mode & S_IWGRP)) {
            printf("is y\n");
        } else {
            printf("is n\n");
        }

        strcpy(cmd, "ls -l ");
        strcat(cmd, ttyname(STDIN_FILENO));
        return system(cmd);
    }

    if (argv[1][0] == 'y') {
        strcpy(cmd, "chmod a+w ");
        strcat(cmd, ttyname(STDIN_FILENO));
        return system(cmd);
    } else if (argv[1][0] == 'n') {
        strcpy(cmd, "chmod go-w ");
        strcat(cmd, ttyname(STDIN_FILENO));
        return system(cmd);
    } else {
        printf("usage: omesg [y/n]");
        return -1;
    }

    return 0;
}
