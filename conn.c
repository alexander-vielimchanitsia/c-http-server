/**
 * Stage 1
 * 
 * Set up network connections
 * and pass each connection to the next stage (handle requests)
 */

#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>

#include "conn.h"


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
    address.sin_port = htons(PORT);
    memset(address.sin_zero, 0, sizeof address.sin_zero);

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
        printf("starting to accept connections...\n");
        if ((new_connection = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("Failed to accept a new connection");
            exit(EXIT_FAILURE);
        }
        queue_push(queue, (void *)&new_connection);
    }
}

pthread_t *start_accept_connections(queue_t *queue)
{
    pthread_t *thread;
    pthread_create(thread, NULL, (void *)&setup_conn, (void *)queue);
    return thread;
}
