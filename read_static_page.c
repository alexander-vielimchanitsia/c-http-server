/**
 * Stage 3
 *
 * fetch static page
 */
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "queue.h"
#include "requests.h"
#include "utils.h"
#include "read_static_page.h"


#define TEMPLATES "./templates"
#define MAX_FILE_LENGTH 65536  // 64K


void start_process_read_static_pages(queue_t *rsp_queue)
{
    // TODO: split the work by more threads?
    pthread_t *thread;
    pthread_create(thread, NULL, (void *)&read_static_pages, (void *)rsp_queue);
}

void read_static_pages(queue_t *rsp_queue)
{
    request_msg_t *msg;
    while (1) {
        queue_pop(rsp_queue, msg);
        printf("msg: %s\n", msg->request->url->path);
    }
}

void read_file(char *path, char *buf)
{
    char file_path[strlen(path) + strlen(TEMPLATES)];
    path_combine(file_path, TEMPLATES, path);

    FILE *fp = fopen(file_path, "r");
    fgets(buf, MAX_FILE_LENGTH, fp);
    fclose(fp);
}
