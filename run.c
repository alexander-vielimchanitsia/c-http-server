#include <pthread.h>
#include <stdio.h>

#include "conn.h"
#include "requests.h"
#include "queue.h"
#include "read_static_page.h"
#include "send_page.h"


#define MAX_CONN_QUEUE_ITEMS 10
#define MAX_GDP_QUEUE_ITEMS  20
#define MAX_RSP_QUEUE_ITEMS  20
#define MAX_RESP_QUEUE_ITEMS 20


int main(int argc, char const *argv[])
{
    queue_t *conn_queue = queue_init(MAX_CONN_QUEUE_ITEMS);
    queue_t *gdp_queue = queue_init(MAX_RSP_QUEUE_ITEMS);
    queue_t *rsp_queue = queue_init(MAX_RSP_QUEUE_ITEMS);
    queue_t *resp_queue = queue_init(MAX_RESP_QUEUE_ITEMS);

    pthread_t *conn_thread = start_accept_connections(conn_queue);
    start_handle_connections(conn_queue, rsp_queue, gdp_queue);
    start_process_read_static_pages(rsp_queue);
    start_process_send_pages(resp_queue);

    pthread_join(*conn_thread, NULL);
    return 0;
}
