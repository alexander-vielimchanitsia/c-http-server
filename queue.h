#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <pthread.h>
#include "cv.h"
#include "lock.h"


typedef struct Queue {
    // syncronization variables
    pthread_mutex_t lock;
    pthread_cond_t item_pushed;
    pthread_cond_t item_popped;

    // state variables
    int max_items;
    int front;
    int next_item;
    void **items;
} queue_t;

void queue_destroy(queue_t *q);
queue_t *queue_init(int max_items);
void queue_push(queue_t *q, void *item);

// void queue_pop(queue_t *q, void *item);
#define queue_pop(q, item) ({                           \
    aquire_lock(&q->lock);                              \
    while (q->front >= q->next_item)                    \
        wait_cv(&q->item_pushed, &q->lock);             \
    item = q->items[q->front++ % q->max_items];         \
    signal_cv(&q->item_popped);                         \
    release_lock(&q->lock);                             \
})

#endif
