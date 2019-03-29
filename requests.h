#ifndef _REQUESTS_H_
#define _REQUESTS_H_

#include "queue.h"

enum Method { GET, POST };

struct Header {
    char *name;
    char *value;
    struct Header *next;
};

struct Url {
    char *host;
    int port;
    char *path;
};

typedef struct Request {
    enum Method method;
    struct Header *headers;
    struct Url *url;
    char *body;
} request_t;

void start_handle_connections(queue_t *conn_queue);
void handle_connection(queue_t *conn_queue);
void read_stream(int conn, char *buf);
request_t *parse_request(char *raw);


#endif
