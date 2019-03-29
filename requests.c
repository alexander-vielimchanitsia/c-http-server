/**
 * Stage 2
 * 
 * Get data from a connection & parse the data.
 * Using several threads, each gets a connection from the incoming queue,
 * read request from the connection,
 * parse it - determine what page is being requested, check to see if it's alredy cached
 */

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "queue.h"
#include "requests.h"

#define WORKERS_NUM 4
#define MAX_REQUEST_BUF 65536  // 64K


void start_handle_connections(queue_t *conn_queue)
{
    // start workers
    pthread_t workers[WORKERS_NUM];
    int i;
    for (i = 0; i < WORKERS_NUM; i++)
        pthread_create(&workers[i], NULL, (void *)&handle_connection, (void *)conn_queue);
}

/* Worker */
void handle_connection(queue_t *conn_queue)
{
    int *connection;
    char request_buf[MAX_REQUEST_BUF];
    while (1) {
        printf("wait for a connection\n");
        queue_pop(conn_queue, connection);
        printf("got a connection: %d\n", *connection);
        read_stream(*connection, request_buf);
        printf("buffer: %s\n", request_buf);
        request_t *request = parse_request(request_buf);
        close(*connection);
    }
}

void read_stream(int conn, char *buf)
{
    memset(buf, 0, MAX_REQUEST_BUF);
    int bytes_read = read(conn, buf, MAX_REQUEST_BUF-1);
    if (bytes_read < 0) {
        printf("Failed to read request from conn=%d\n", conn);
        exit(EXIT_FAILURE);
    }
}

request_t *parse_request(char *raw)
{
    request_t *request = calloc(1, sizeof(request_t));
    return request;
}
