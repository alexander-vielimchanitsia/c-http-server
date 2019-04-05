#include <stdio.h>
#include <stdlib.h>

#include "../response.h"


int main()
{
    response_t *response = malloc(sizeof(response_t));
    response->status = 200;
    response->proto = "HTTP/1.1";
    response->body = "<html><body><h1>Some text</h1></body></html>";
    // headers
    header_t *h1 = malloc(sizeof(header_t));
    h1->name = "Content-Type";
    h1->value = "text/html";
    h1->next = NULL;
    header_t *h2 = malloc(sizeof(header_t));
    h2->name = "Content-Length";
    h2->value = "111";
    h2->next = h1;
    response->headers = malloc(sizeof(header_t));
    response->headers->name = "Connection";
    response->headers->value = "Keep-Alive";
    response->headers->next = h2;

    char response_string[MAX_RESPONSE_LENGTH];
    response_to_string(response, response_string);
    printf("response: '%s'\n", response_string);
    return 0;
}
