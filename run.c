#include <pthread.h>
#include "conn.h"
#include "queue.h"

#define MAX_CONN_QUEUE_ITEMS 10


int main(int argc, char const *argv[])
{
    queue_t *conn_queue = queue_init(MAX_CONN_QUEUE_ITEMS);

    pthread_t *conn_thread = start_accept_connections(conn_queue);

    pthread_join(*conn_thread, NULL);
    return 0;
}
