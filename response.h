#ifndef _RESPONSE_H_
#define _RESPONSE_H_

#include "requests.h"
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

const char *get_status_text(short int status_code);
response_t *create_response(const char *proto, const char *body, int file_length, const char *mime);
response_t *create_404_response(request_t *request);
response_t *create_500_response(request_t *request);
response_msg_t *create_response_msg(response_t *response, int *connection);
void response_to_string(response_t *response, char *buf);
void free_response(response_t *response);
void free_response_msg(response_msg_t *msg);

#endif
