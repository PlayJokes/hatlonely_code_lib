// @file client.c
// @desc unix socket client sample
// @auth hatlonely
// @date 2014-6-15

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

const int BUF_SIZE = 1024;

int main() {
    int socket_fd;
    struct sockaddr_in server_address;

    char read_buffer[BUF_SIZE];

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        perror("socket error");
    }

    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(1444);
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);

    if (connect(socket_fd, (struct sockaddr *)&server_address, 
        sizeof(server_address)) == -1) {
        perror("connect error");
    }

    write(socket_fd, "hatlonely", strlen("hatlonely") + 1);
    read(socket_fd, read_buffer, sizeof(read_buffer));
    printf("%s", read_buffer);
}
