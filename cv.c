#include <assert.h>
#include <pthread.h>


void create_cv(pthread_cond_t *cv)
{
    int err = pthread_cond_init(cv, NULL);
    assert(!err);
}

void wait_cv(pthread_cond_t *cv, pthread_mutex_t *lock)
{
    int err = pthread_cond_wait(cv, lock);
    assert(!err);
}

void signal_cv(pthread_cond_t *cv)
{
    int err = pthread_cond_signal(cv);
    assert(!err);
}

void broadcast_cv(pthread_cond_t *cv)
{
    int err = pthread_cond_broadcast(cv);
    assert(!err);
}
