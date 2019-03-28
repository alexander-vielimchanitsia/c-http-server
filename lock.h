#ifndef _LOCK_H_
#define _LOCK_H_

#include <pthread.h>

void create_lock(pthread_mutex_t *lock);
void aquire_lock(pthread_mutex_t *lock);
void release_lock(pthread_mutex_t *lock);

#endif
