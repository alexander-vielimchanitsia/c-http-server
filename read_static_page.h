#ifndef _READ_STATIC_PAGE_H_
#define _READ_STATIC_PAGE_H_

#include "queue.h"

typedef struct RSPWorkerArgs {
    queue_t *rsp_queue;
    queue_t *resp_queue;
} rsp_worker_args_t;

void start_process_read_static_pages(queue_t *rsp_queue, queue_t *resp_queue);
void read_static_pages(rsp_worker_args_t *args);
void read_file(char *path, char *buf);

#endif
