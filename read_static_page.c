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
        ssize_t file_length = read_file(req_msg->request->url->path, file_content);
        if (file_length < 0)
        {
            printf("Failed to read file for url='%s'\n", req_msg->request->url->path);
            // TODO: send 500 status instead
            close(*req_msg->connection);
            continue;
        }
        response = create_response(req_msg->request->proto, file_content, file_length);
        resp_msg = malloc(sizeof(response_msg_t));
        resp_msg->connection = req_msg->connection;
        resp_msg->response = response;
        queue_push(args->resp_queue, resp_msg);
        free_request(req_msg->request);
        free(req_msg);
    }
}

ssize_t read_file(char *url_path, char *buf)
{
    // get the file path
    char file_path[strlen(TEMPLATES) + strlen(url_path) + 1];
    path_combine(file_path, TEMPLATES, url_path);
    // read the file
    int file = open(file_path, O_RDONLY);
    ssize_t bytes_read = read(file, buf, MAX_FILE_LENGTH);
    close(file);
    return bytes_read;
}
