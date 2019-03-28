#include <assert.h>
#include <pthread.h>


void create_lock(pthread_mutex_t *lock)
{
    int err = pthread_mutex_init(lock, NULL);
    assert(!err);
}

void aquire_lock(pthread_mutex_t *lock)
{
    int err = pthread_mutex_lock(lock);
    assert(!err);
}

void release_lock(pthread_mutex_t *lock)
{
    int err = pthread_mutex_unlock(lock);
    assert(!err);
}
