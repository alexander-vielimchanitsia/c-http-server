#ifndef _CV_H_
#define _CV_H_

#include <pthread.h>

void create_cv(pthread_cond_t *cv);
void wait_cv(pthread_cond_t *cv, pthread_mutex_t *lock);
void signal_cv(pthread_cond_t *cv);
void broadcast_cv(pthread_cond_t *cv);

#endif
