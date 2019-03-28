#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../queue.h"


const static char *TEST_ITEM = "test1";


void push_test_item(queue_t *q)
{
    printf("start pushing\n");
    queue_push(q, (void *)TEST_ITEM);
    printf("pushed: %s\n", TEST_ITEM);
}

void pop_test_item(queue_t *q)
{
    char *item;
    printf("start popping\n");
    queue_pop(q, item);
    printf("popped: %s\n", item);
    assert(!strcmp(TEST_ITEM, item));
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

