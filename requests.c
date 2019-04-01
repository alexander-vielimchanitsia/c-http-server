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
    for (int i = 0; i < WORKERS_NUM; i++)
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

// TODO: move to utils.c?
/**
 * !! Returns a pointer to a char into `*s` char array, NOT A NEW ARRAY
 * !! Sets a null-value into the place of `*delim` in the `*s` char array
 * (s="GET / HTTP/1.1\r\n", delim=" ") -> returns "GET", s="/ HTTP/1.1\r\n"
 */
char *get_next_http_value(char **s, char *delim)
{
    char *value = *s;
    char *end = *s + strcspn(*s, delim);  // "GET / HTTP" -> " / HTTP"
    if (*end)
        *end++ = '\0';
    *s = end;
    return value;
}

request_t *parse_request(char *raw)
{
    request_t *request = calloc(1, sizeof(request_t));
    if (!request) {
        printf("Failed to allocate request_t");
        return NULL;
    }

    // TODO: add check validation (like whether there're all required fileds)

    // method
    char *method = get_next_http_value(&raw, " ");
    if (strcmp(method, "GET") == 0)
        request->method = M_GET;
    else if (strcmp(method, "POST") == 0)
        request->method = M_POST;
    else
        request->method = M_UNKNOWN;
    printf("method: '%d' | raw: '%s'\n", request->method, raw);

    // path
    char *path = get_next_http_value(&raw, " ");
    request->url = calloc(1, sizeof(url_t));
    request->url->path = malloc(strlen(path));
    strcpy(request->url->path, path);
    printf("path: '%s'\n", request->url->path);

    // protocol
    char *proto = get_next_http_value(&raw, "\r\n");
    request->proto = malloc(strlen(proto));
    strcpy(request->proto, proto);
    printf("protocol: '%s'\n", request->proto);
 
    // headers

    // body

    return request;
}

header_t *parser_headers()
{
    return NULL;
}

void free_request(request_t *request)
{

}

void free_header(header_t *header)
{

}
