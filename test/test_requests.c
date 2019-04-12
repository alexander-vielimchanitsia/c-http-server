#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../requests.h"


int main(void) {
    char *data = "GET / HTTP/1.1\r\n"
                 "Host: 127.0.0.1:8080\r\n"
                 "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
                 "Upgrade-Insecure-Requests: 1\r\n"
                 "User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_3) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/12.0.3 Safari/605.1.15\r\n"
                 "Accept-Language: en-us\r\n"
                 "Accept-Encoding: gzip, deflate\r\n"
                 "Connection: keep-alive\r\n"
                 "\r\n"
                 "body data";
    char *raw = malloc(strlen(data)+1);
    strcpy(raw, data);

    request_t *req = parse_request(raw);

    printf("Method: %d\n", req->method);
    printf("url: %s\n", req->url->host);
    printf("Headers:\n");
    for (header_t *h = req->headers; h; h = h->next)
        printf("%s: %s\n", h->name, h->value);
    printf("body:\n%s\n", req->body);
    free_request(req);
    free(raw);
    return 0;
}
