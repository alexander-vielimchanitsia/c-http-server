/**
 * Stage 1
 * 
 * Set up network connections
 * and pass each connection to the next stage (handle requests)
 */

#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

#include "queue.h"


#define PORT 8080
#define MAX_PENDING_CONN 10


void setup_conn(queue_t *queue)
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // address init
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    memset(address.sin_zero, '\0', sizeof address.sin_zero);

    if (bind(server_fd, (struct sockaddr *)&address, addrlen) < 0)
    {
        perror("Failed to bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_PENDING_CONN) < 0)
    {
        perror("Failed to start listening");
        exit(EXIT_FAILURE);
    }

    int new_connection;
    while (1)
    {
        if ((new_connection = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("Failed to accept a new connection");
            exit(EXIT_FAILURE);
        }
        queue_put(queue, (void *)&new_connection);
    }
}
