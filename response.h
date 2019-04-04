#ifndef _RESPONSE_H_
#define _RESPONSE_H_

#include "common_http.h"


typedef struct Response {
    char *proto;
    short int status;
    header_t *headers;
    char *body;
} response_t;

#endif
