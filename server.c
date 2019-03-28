#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


#define PORT 8080
#define MAX_PENDING_CONN 10


int main()
{
    long valread;
    int new_socket;
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) // == 0?
    {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // memset((char *)&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    // address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    memset(address.sin_zero, '\0', sizeof address.sin_zero);

    // char *hello = "Hello from server";
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";

    if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_PENDING_CONN) < 0)
    {
        perror("Failed to start listening");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        printf("\n------------Waiting for new connections------------\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("Failed to accept a new connection");
            exit(EXIT_FAILURE);
        }

        char buffer[30000] = {0};
        valread = read(new_socket, buffer, 30000);
        printf("buffer: %s\n", buffer);
        write(new_socket, hello, strlen(hello));
        printf("------------Hello message sent------------\n");
        close(new_socket);
    }
    return 0;
}
