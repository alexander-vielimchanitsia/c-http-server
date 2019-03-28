#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../queue.h"


void push_test_item(queue_t *q)
{
    char str[] = "test1";
    char *data = malloc(strlen(str));
    strcpy(data, str);
    printf("start pushing\n");
    queue_push(q, data);
    printf("pushed: %s\n", data);
}

void pop_test_item(queue_t *q)
{
    char *item;
    printf("start popping\n");
    queue_pop(q, item);
    printf("popped: %s\n", item);
}

int main()
{
    queue_t *queue = queue_init(10);

    pthread_t pop_thread;
    pthread_create(&pop_thread, NULL, (void *)&pop_test_item, (void *)queue);

    pthread_t push_thread;
    pthread_create(&push_thread, NULL, (void *)&push_test_item, (void *)queue);

    pthread_join(pop_thread, NULL);
}

