#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cv.h"
#include "lock.h"
#include "queue.h"


void queue_destroy(queue_t *q)
{

}

queue_t *queue_init(int max_items)
{
    queue_t *queue = (queue_t *)calloc(1, sizeof(queue_t));
    queue->items = malloc(max_items * sizeof(void *));
    queue->front = 0;
    queue->next_item = 0;
    queue->max_items = max_items;

    // synchronization variables
    create_lock(&queue->lock);
    create_cv(&queue->item_pushed);
    create_cv(&queue->item_popped);
    return queue;
}

void queue_push(queue_t *q, void *item)
{
    aquire_lock(&q->lock);
    while ((q->next_item - q->front) >= q->max_items)
        wait_cv(&q->item_popped, &q->lock);
    q->items[q->next_item++ % q->max_items] = item;
    signal_cv(&q->item_pushed);
    release_lock(&q->lock);
}
