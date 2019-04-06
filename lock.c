#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


void create_lock(pthread_mutex_t *lock)
{
    int err = pthread_mutex_init(lock, NULL);
    assert(!err);
}

void aquire_lock(pthread_mutex_t *lock)
{
    int err = pthread_mutex_lock(lock);
    if (err) {
        printf("aquire_lock: ");
        switch (err) {
        case EAGAIN:
            printf("The mutex could not be acquired because the maximum "
                    "number of recursive locks for mutex has been exceeded\n");
            break;
        case EDEADLK:
            printf("The current thread already owns the mutex, and the "
                    "mutex has a kind attribute of __MUTEX_NONRECURSIVE\n");
            break;
        case EINVAL:
            printf("The value specified by mutex is not valid\n");
            break;
        default:
            printf("An error(%d) while aquiring lock has occurred, errno=%d\n", err, errno);
            break;
        }
        exit(-1);
    }
}

void release_lock(pthread_mutex_t *lock)
{
    int err = pthread_mutex_unlock(lock);
    assert(!err);
}
