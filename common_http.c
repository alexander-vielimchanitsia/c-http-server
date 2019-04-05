#include <stdlib.h>
#include "common_http.h"


void free_header(header_t *header)
{
    if (header) {
        free(header->name);
        free(header->value);
        free_header(header->next);
        free(header);
    }
}
