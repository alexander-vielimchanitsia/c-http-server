#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common_http.h"
#include "utils.h"
#include "response.h"


const char *get_status_text(short int status_code)
{
    switch (status_code) {
    case 200:
        return "OK";
    case 404:
        return "Not Found";
    case 500:
        return "Internal Server Error";
    default:
        return "UNKNOWN STATUS CODE";
    }
}

response_t *create_response(const char *proto, const char *body, int file_length)
{
    response_t *response = malloc(sizeof(response_t));
    if (response == NULL) {
        printf("create_response: failed to allocate `response_t`\n");
        return NULL;
    }
    response->proto = malloc(strlen(proto)+1);
    if (response->proto == NULL) {
        printf("create_response: failed to allocate `response->proto`\n");
        return NULL;
    }
    response->body = malloc(file_length+1);
    if (response->body == NULL) {
        printf("create_response: failed to allocate `response->body`\n");
        return NULL;
    }
    strcpy(response->proto, proto);
    strcpy(response->body, body);

    // TODO: use mime parser instead
    header_t *header = create_header("Content-Type", "text/html", NULL);
    // TODO: prototype; refactor it
    char *content_length = malloc(6);
    itoa(file_length, content_length);
    response->headers = create_header("Content-Length", content_length, header);
    return response;
}

void response_to_string(response_t *response, char *buf)
{
    char status[4];
    itoa(response->status, status);

    memset(buf, 0, MAX_RESPONSE_LENGTH);
    strcat(buf, response->proto);
    strcat(buf, " ");
    strcat(buf, status);
    strcat(buf, " ");
    strcat(buf, get_status_text(response->status));
    strcat(buf, "\r\n");
    // headers
    for (header_t *h = response->headers; h; h = h->next) {
        strcat(buf, h->name);
        strcat(buf, ": ");
        strcat(buf, h->value);
        strcat(buf, "\r\n");
    }
    // body
    strcat(buf, "\r\n");
    strcat(buf, response->body);
}

void free_response(response_t *response)
{
    free(response->proto);
    free(response->body);
    free_header(response->headers);
    free(response);
}
