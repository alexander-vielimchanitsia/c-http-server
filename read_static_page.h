#ifndef _READ_STATIC_PAGE_H_
#define _READ_STATIC_PAGE_H_

#include "queue.h"


void start_process_read_static_pages(queue_t *rsp_queue);
void read_static_pages(queue_t *rsp_queue);

#endif
