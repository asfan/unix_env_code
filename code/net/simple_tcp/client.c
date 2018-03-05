/**
 * 最简单的tcp client
 */

#include "apue.h"

#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 64

int
main(int argc, char *argv[])
{
    if (argc < 2)
        err_quit("Usage: %s [port]\n", argv[0]);

    int port = atoi(argv[1]);

    int client_socket_fd, n;
    struct sockaddr_in server_addr;
    struct hostent *server;
    char *hostname;
    char buffer[BUFFER_SIZE];

    // init
    memset(buffer, 0, sizeof(buffer));

    //create socket
    client_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket_fd < 0)
        err_quit("process can't create a socket!\n");

    memset((char *) &server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(client_socket_fd, &server_addr, sizeof(server_addr)) < 0)
        err_quit("socket can't connect to the server!\n");

    printf("please enter message:");
    while(1)
    {
        char loc = fgets(buffer, sizeof(buffer), stdin);
        if (loc == NULL) break;

        n = write(client_socket_fd, buffer, strlen(buffer));
        if (n < 0)
            err_quit("error write to the server\n");

        memset(buffer, 0, sizeof(buffer));
        n = read(client_socket_fd, buffer, sizeof(buffer));
        if (n < 0)
            err_quit("error read from the server\n");

        printf("ack from server is %s", buffer);
    }
    
    close(client_socket_fd);

    return 0;
}
