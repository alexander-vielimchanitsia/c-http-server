/**
 * Stage 3
 *
 * fetch static page
 */
#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "queue.h"
#include "response.h"
#include "requests.h"
#include "utils.h"
#include "read_static_page.h"


#define TEMPLATES "./templates"
#define MAX_FILE_LENGTH 65536  // 64K


void start_process_read_static_pages(queue_t *rsp_queue, queue_t *resp_queue)
{
    // TODO: split the work by more threads?
    pthread_t *thread = malloc(sizeof(pthread_t));
    rsp_worker_args_t *args = malloc(sizeof(rsp_worker_args_t));
    args->rsp_queue = rsp_queue;
    args->resp_queue = resp_queue;
    pthread_create(thread, NULL, (void *)&read_static_pages, args);
}

/* Worker */
void read_static_pages(rsp_worker_args_t *args)
{
    response_t *response;
    char file_content[MAX_FILE_LENGTH];
    response_msg_t *resp_msg;
    request_msg_t *req_msg;
    while (1)
    {
        queue_pop(args->rsp_queue, req_msg);
        printf("req_msg: %s\n", req_msg->request->url->path);

        // get filepath
        char filepath[strlen(TEMPLATES) + strlen(req_msg->request->url->path) + 1];
        path_combine(filepath, TEMPLATES, req_msg->request->url->path);

        // does this file exist?
        if (access(filepath, F_OK) < 0) {
            response = create_404_response(req_msg->request);
            push_response(args->resp_queue, req_msg->connection, response);
            free_request_msg(req_msg);
            continue;
        }

        ssize_t file_length = read_file(filepath, file_content);
        if (file_length < 0)
            response = create_500_response(req_msg->request);
        else {
            char *mime = get_mime_type(filepath);
            response = create_response(req_msg->request->proto, file_content, file_length, mime);
        }
        push_response(args->resp_queue, req_msg->connection, response);
        free_request_msg(req_msg);
    }
}

void push_response(queue_t *q, int *connection, response_t *response)
{
    response_msg_t *resp_msg = create_response_msg(response, connection);
    queue_push(q, resp_msg);
}

ssize_t read_file(char *filepath, char *buf)
{
    int file = open(filepath, O_RDONLY);
    ssize_t bytes_read = read(file, buf, MAX_FILE_LENGTH);
    close(file);
    return bytes_read;
}
