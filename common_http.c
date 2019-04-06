#include <stdlib.h>
#include <string.h>

#include "common_http.h"


header_t *create_header(char *name, char *value, header_t *next)
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
