/**
 * Stage 4
 *
 * send a page back to a client
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "response.h"
#include "queue.h"
#include "send_page.h"


void start_process_send_pages(queue_t *resp_queue)
{
    pthread_t *thread = malloc(sizeof(pthread_t));
    pthread_create(thread, NULL, (void *)&send_pages, (void *)resp_queue);
}

void send_pages(queue_t *resp_queue)
{
    response_msg_t *msg;
    while (1)
    {
        queue_pop(resp_queue, msg);
        send_response(*msg->connection, msg->response);
        close(*msg->connection);
        free_response_msg(msg);
    }
}

void send_response(int conn, response_t *response)
{
    char response_text[MAX_RESPONSE_LENGTH];
    response_to_string(response, response_text);
    int content_length = strlen(response_text); // TODO: get the data from response struct
    write(conn, response_text, content_length);
}
