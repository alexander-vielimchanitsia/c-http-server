/**
 * Stage 4
 *
 * send a page back to a client
 */
#include <pthread.h>
#include <stdlib.h>

#include "response.h"
#include "queue.h"
#include "send_page.h"


void start_process_send_pages(queue_t *resp_queue)
{
    pthread_t *thread;
    pthread_create(thread, NULL, (void *)&send_pages, (void *)resp_queue);
}

void send_pages(queue_t *resp_queue)
{
    response_msg_t *msg;
    while (1)
    {
        queue_pop(resp_queue, msg);
        send_response(msg->response);
        free_response(msg->response);
        free(msg);
    }
}

void send_response(response_t *response)
{

}