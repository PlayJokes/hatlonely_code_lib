// @file server.c
// @desc unix socket server sample
// @auth hatlonely
// @date 2014-6-15

#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

const int BUF_SIZE = 1024;

int main() 
{
    int listen_fd, connect_fd;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length;

    char read_buffer[BUF_SIZE];
    char write_buffer[BUF_SIZE];

    if ((listen_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
        perror("socket error");
    }

    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(1444);

    if (bind(listen_fd, (const struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("bind error");
    }

    if (listen(listen_fd, 10) == -1) {
        perror("listen error");
    }

    for (;;) {
        client_address_length = sizeof(client_address);
        if ((connect_fd = accept(listen_fd, (struct sockaddr *)&client_address, 
            &client_address_length)) == -1) {
            perror("accept error");
        }

        read(connect_fd, read_buffer, sizeof(read_buffer));
        snprintf(write_buffer, sizeof(write_buffer), "hello %s\n", read_buffer);
        write(connect_fd, write_buffer, strnlen(write_buffer, sizeof(write_buffer)));
        printf("%s", write_buffer);
    }
}