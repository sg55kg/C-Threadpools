#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <pthread.h>
#include "task.h"

typedef struct
{
    pthread_t *threads;
    int thread_count;
    task_t* task_queue_head;
    int running;
    pthread_mutex_t mutex;       // Mutex to protect the queue
    pthread_cond_t cond;         // Condition variable to signal availability of tasks
} ThreadPool;

extern ThreadPool* global_thread_pool;

ThreadPool* thread_pool_create(int num_threads);
void* worker_thread_function(void* arg);
void thread_pool_destroy(ThreadPool* pool);
void task_enqueue(ThreadPool* pool, task_t* task);
task_t* task_dequeue(ThreadPool* pool);

#endif // THREAD_POOL_H
