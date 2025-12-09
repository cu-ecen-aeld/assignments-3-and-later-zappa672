#include "threading.h"

#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
// #define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{
    thread_data_t* thread_func_args = (thread_data_t*) thread_param;

    usleep(1000 * thread_func_args->wait_to_obtain_ms);

    int r = pthread_mutex_lock(thread_func_args->mutex);
    if (r) {
        ERROR_LOG("pthread_mutex_lock fail: %s(%d)", strerror(r), r);
        thread_func_args->thread_complete_success = false;
        return thread_param;
    }

    usleep(1000 * thread_func_args->wait_to_release_ms);

    r = pthread_mutex_unlock(thread_func_args->mutex);
    if (r) {
        ERROR_LOG("pthread_mutex_unlock fail: %s(%d)", strerror(r), r);
        thread_func_args->thread_complete_success = false;
        return thread_param;
    }

    thread_func_args->thread_complete_success = true;
    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex, int wait_to_obtain_ms, int wait_to_release_ms)
{
    thread_data_t* thread_func_args = (thread_data_t*) malloc(sizeof(thread_data_t));
    thread_func_args->mutex = mutex;
    thread_func_args->wait_to_obtain_ms = wait_to_obtain_ms;
    thread_func_args->wait_to_release_ms = wait_to_release_ms;
    thread_func_args->thread_complete_success = false; 

    int r = pthread_create(thread, NULL, threadfunc, thread_func_args);
    if (r) {
        ERROR_LOG("pthread_create fail: %s(%d)", strerror(r), r);
        return false;
    }

    return true;
}

