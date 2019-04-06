#ifndef _RESPONSE_H_
#define _RESPONSE_H_

#include "common_http.h"

#define MAX_RESPONSE_LENGTH 65536  // 64K

typedef struct Response {
    char *proto;
    short int status;
    header_t *headers;
    char *body;
} response_t;

typedef struct ResponseMsg {
    int *connection;
    response_t *response;
} response_msg_t;

response_t *create_response(const char *proto, const char *body, int file_length);
void response_to_string(response_t *response, char *buf);
void free_response(response_t *response);
const char *get_status_text(short int status_code);

#endif
