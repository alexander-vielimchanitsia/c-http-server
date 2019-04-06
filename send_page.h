#ifndef _SEND_PAGE_H_
#define _SEND_PAGE_H_

#include "response.h"
#include "queue.h"


void start_process_send_pages(queue_t *resp_queue);
void send_pages(queue_t *resp_queue);
void send_response(int conn, response_t *response);

#endif
