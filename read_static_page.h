#ifndef _READ_STATIC_PAGE_H_
#define _READ_STATIC_PAGE_H_

#include "response.h"
#include "queue.h"

typedef struct RSPWorkerArgs {
    queue_t *rsp_queue;
    queue_t *resp_queue;
} rsp_worker_args_t;

void start_process_read_static_pages(queue_t *rsp_queue, queue_t *resp_queue);
void read_static_pages(rsp_worker_args_t *args);
ssize_t read_file(char *filepath, char *buf);
void push_response(queue_t *response_queue, int *connection, response_t *response);

#endif
