#ifndef _REQUESTS_H_
#define _REQUESTS_H_

#include "queue.h"

enum Method { M_UNKNOWN, M_GET, M_POST };

typedef struct Header {
    char *name;
    char *value;
    struct Header *next;
} header_t;

typedef struct Url {
    char *protocol;
    char *host;
    int port;
    char *path;
} url_t;

typedef struct Request {
    enum Method method;
    header_t *headers;
    url_t *url;
    char *body;
    char *proto;
} request_t;

typedef struct RequestMsg {
    queue_t *conn_queue;
    request_t *request;
} request_msg_t;

typedef struct WorkerArgs {
    queue_t *conn_queue;
    queue_t *rsp_queue;
    queue_t *gdp_queue;
} worker_args_t;

void start_handle_connections(queue_t *conn_queue, queue_t *rsp_queue, queue_t *gdp_queue);
void handle_connection(worker_args_t *args);
void read_stream(int conn, char *buf);
request_t *parse_request(char *raw);
header_t *parse_headers(char **rawp);
void free_request(request_t *request);
void free_header(header_t *header);


#endif
