#ifndef _COMMON_HTTP_H_
#define _COMMON_HTTP_H_

typedef struct Header {
    char *name;
    char *value;
    struct Header *next;
} header_t;

#endif
