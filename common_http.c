#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "common_http.h"


header_t *create_header(const char *name, const char *value, header_t *next)
{
    header_t *header = malloc(sizeof(header_t));
    if (header == NULL)
        return NULL;
    header->name = malloc(strlen(name)+1);
    if (header->name == NULL)
        return NULL;
    header->value = malloc(strlen(value)+1);
    if (header->value == NULL)
        return NULL;
    strcpy(header->name, name);
    strcpy(header->value, value);
    header->next = next;
    return header;
}

void free_header(header_t *header)
{
    if (header) {
        free(header->name);
        free(header->value);
        free_header(header->next);
        free(header);
    }
}


char *get_mime_type(char *filename)
{
    char *ext = get_file_ext(filename);
    if (strcmp(ext, "html") == 0)                            return "text/html";
    if (strcmp(ext, "css") == 0)                             return "text/css";
    if (strcmp(ext, "js") == 0)                              return "application/javascript";
    if (strcmp(ext, "json") == 0)                            return "application/json";
    if (strcmp(ext, "txt") == 0)                             return "text/plain";
    if (strcmp(ext, "jpeg") == 0 || strcmp(ext, "jpg") == 0) return "text/jpg";
    if (strcmp(ext, "gif") == 0)                             return "text/gif";
    if (strcmp(ext, "png") == 0)                             return "text/png";
    return DEFAULT_MIME_TYPE;
}
