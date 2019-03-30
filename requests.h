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
} request_t;


void start_handle_connections(queue_t *conn_queue);
void handle_connection(queue_t *conn_queue);
void read_stream(int conn, char *buf);
request_t *parse_request(char *raw);
void free_request(request_t *request);
void free_header(header_t *header);


#endif
