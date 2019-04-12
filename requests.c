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


void start_handle_connections(queue_t *conn_queue, queue_t *rsp_queue, queue_t *gdp_queue)
{
    // start workers
    pthread_t workers[WORKERS_NUM];
    req_worker_args_t *args = malloc(sizeof(req_worker_args_t));
    args->conn_queue = conn_queue;
    args->gdp_queue = gdp_queue;
    args->rsp_queue = rsp_queue;
    for (int i = 0; i < WORKERS_NUM; i++)
        pthread_create(&workers[i], NULL, (void *)&handle_connection, (void *)args);
}

/* Worker */
void handle_connection(req_worker_args_t *args)
{
    int *connection;
    char request_buf[MAX_REQUEST_BUF];
    while (1) {
        printf("wait for a connection\n");
        queue_pop(args->conn_queue, connection);
        printf("got a connection: %d\n", *connection);
        read_stream(*connection, request_buf);
        printf("request(%d): %s\n", *connection, request_buf);
        request_t *request = parse_request(request_buf);
        if (request) {
            // TODO: try to get the page from the cache
            // page = cache_get(request);
            request_msg_t *msg = malloc(sizeof(request_msg_t));
            msg->connection = connection;
            msg->request = request;
            // TODO: push to gdp_queue for dynamic pages
            queue_push(args->rsp_queue, msg);
        } else {
            printf("Failed to parse request(%d)", *connection);
            close(*connection);
        }
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
    if (*end) {
        *end++ = '\0';
        // FIXME: write own implementation of this function for correct behavior
        // FIXME: do not need to skip miltiple delimetrs that are together
        // FIXME: the correct behavior is MIN((strlen(delim)-1), strspn(end, delim)) but it is not optimized one
        // end += strspn(end, delim);
        end += strlen(delim)-1;
    }
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
    // printf("method: '%d' | raw: '%s'\n", request->method, raw);

    // path
    char *path = get_next_http_value(&raw, " ");
    request->url = calloc(1, sizeof(url_t));
    request->url->path = malloc(strlen(path)+1);
    strcpy(request->url->path, path);
    // printf("path: '%s'\n", request->url->path);

    // protocol
    char *proto = get_next_http_value(&raw, "\r\n");
    request->proto = malloc(strlen(proto)+1);
    strcpy(request->proto, proto);
    // printf("protocol: '%s'\n", request->proto);
 
    // headers
    request->headers = parse_headers(&raw);
    // printf("headers:\n");
    // for (header_t *h = request->headers; h; h = h->next)
    //     printf("'%s': '%s'\n", h->name, h->value);

    // body
    // printf("raw: %s\n", raw);
    // TODO: add it later

    return request;
}

header_t *parse_headers(char **rawp)
{
    char *name, *value;
    header_t *header = NULL;
    header_t *prev_header = NULL;
    while (**rawp != '\r' && **rawp != '\n'
        && *(name = get_next_http_value(rawp, ": ")))
    {
        value = get_next_http_value(rawp, "\r\n");
        if (*value) {
            prev_header = header;
            header = malloc(sizeof(header_t));
            header->next = prev_header;

            header->name = malloc(sizeof(name));
            strcpy(header->name, name);
            header->value = malloc(sizeof(value));
            strcpy(header->value, value);
        } else {
            // TODO: ?
            // free_request() ?
            // free_header() ?
            continue;
        }
    }
    return header;
}

void free_request(request_t *request)
{
    free(request->proto);
    free(request->body);
    free_url(request->url);
    free_header(request->headers);
    free(request);
}

void free_url(url_t *url)
{
    free(url->protocol);
    free(url->host);
    // free(url->port);
    free(url->path);
    free(url);
}
