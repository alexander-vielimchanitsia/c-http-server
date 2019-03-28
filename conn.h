#ifndef _CONN_H_
#define _CONN_H_

#include "queue.h"


#define PORT 8080
#define MAX_PENDING_CONN 10


void setup_conn(queue_t *queue);

#endif
