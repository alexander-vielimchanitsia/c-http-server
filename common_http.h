#ifndef _COMMON_HTTP_H_
#define _COMMON_HTTP_H_

typedef struct Header {
    char *name;
    char *value;
    struct Header *next;
} header_t;

header_t *create_header(char *name, char *value, header_t *next);
void free_header(header_t *header);

#endif
