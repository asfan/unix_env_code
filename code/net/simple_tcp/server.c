/**
 * 最简单的tcp server
 */

#include "apue.h"

#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 32
#define LISTEN_QUEUE 1024

int
main (int argc, char *argv[])
{
    if (argc < 2)
        err_quit("Usage: %s [port]\n", argv[0]);

    int port = atoi(argv[1]);                       //获得server端口

    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];

    memset(buffer, 0, sizeof(buffer));

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
        err_quit("process can't create a socket\n");

    memset((char *) &server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)))
        err_quit("socket fd can't bind on [port] %d\n", port);

    if (listen(server_fd, LISTEN_QUEUE))
        err_quit("process can't listen on socket\n");

    printf("server is listening on port %d:\n", port);

    while(1)
    {
        socklen_t client_len = sizeof(client_addr);
        if ((client_fd = accept(server_fd, (struct sockaddr *) &client_addr, &client_len)) < 0)
            err_quit("can't establish new connection\n");

        while(1)    //连接一次，就一直读到NULL为止。
        {
            int read = recv(client_fd, buffer, BUFFER_SIZE, 0); //这么写，如过传过来的data超出BUFFER_SIZE, 会持续的读和返回，而且是读一包返回一包这样的逻辑
            if (!read) break;
            if (read < 0)
                err_quit("client read fail!\n");

            if (send(client_fd, buffer, read, 0))
                err_quit("client send fail!\n");
        }
    }

    return 0;
}


