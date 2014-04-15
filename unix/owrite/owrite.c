// @file owrite.c
// @desc linux command write support Chinese
// @auth hatlonely (hatlonely@gmail.com)
// @date 2014-4-16


#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <fcntl.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
	int user_num = (argc - 1) / 2;
	char **users = (char **)malloc(sizeof(char *) * user_num);
	char **ptss = (char **)malloc(sizeof(char *) * user_num);

	int i = 0;
	for (i = 0; i < user_num; i += 1) {
		*(users + i) = argv[i * 2 + 1];
		*(ptss + i) = argv[i * 2 + 2];
	}

	char line[BUF_SIZE];

	int fd_index = 0, fd_size = 2;
	int *pts_fd = (int *)malloc(sizeof(int) * fd_size);

	for (i = 0; i < user_num; i++) {
		char ttyname[128];
		snprintf(ttyname, sizeof(ttyname), "/dev/%s", *(ptss + i));
		printf(ttyname);
		int fd = open(ttyname, O_WRONLY);
		if (fd == -1) {
			printf("can not open %s\n", ttyname);
		}
		pts_fd[]
	}


	while (fgets(line, BUF_SIZE, stdin)) {
		/* write(pts_fd, line, strlen(line)); */
	}

	return 0;
}
