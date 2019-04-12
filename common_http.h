#ifndef _COMMON_HTTP_H_
#define _COMMON_HTTP_H_


#define DEFAULT_MIME_TYPE "application/octet-stream"


typedef struct Header {
    char *name;
    char *value;
    struct Header *next;
} header_t;

header_t *create_header(const char *name, const char *value, header_t *next);
void free_header(header_t *header);
char *get_mime_type(char *filename);

#endif
