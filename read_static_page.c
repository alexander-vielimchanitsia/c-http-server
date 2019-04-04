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
    pthread_t *thread;
    rsp_worker_args_t *args = malloc(sizeof(rsp_worker_args_t));
    args->rsp_queue = rsp_queue;
    args->resp_queue = resp_queue;
    pthread_create(thread, NULL, (void *)&read_static_pages, (void *)args);
}

/* Worker */
void read_static_pages(rsp_worker_args_t *args)
{
    response_t *response;
    char file_content[MAX_FILE_LENGTH];
    request_msg_t *msg;
    while (1) {
        queue_pop(args->rsp_queue, msg);
        response = malloc(sizeof(response_t));
        printf("msg: %s\n", msg->request->url->path);
        read_file(msg->request->url->path, file_content);
        printf("file content: %s\n", file_content);
        // remove it
        close(*msg->connection);
    }
}

void read_file(char *path, char *buf)
{
    // get the file path
    char file_path[strlen(TEMPLATES) + strlen(path) + 1];
    path_combine(file_path, TEMPLATES, path);
    // read the file
    int file = open(file_path, O_RDONLY);
    read(file, buf, MAX_FILE_LENGTH);
    close(file);
}
