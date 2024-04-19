#include "threadpool.h"
#include <stdlib.h>
#include <stdio.h>

ThreadPool* global_thread_pool = NULL;

ThreadPool* thread_pool_create(int num_threads)
{
    ThreadPool *pool = malloc(sizeof(ThreadPool));
    
    if (pool == NULL)
    {
        perror("Failed to allocate memory for ThreadPool");
        return NULL;
    }

    pool->running = 1;

    pool->threads = malloc(sizeof(pthread_t) * (long)num_threads);
    if (pool->threads == NULL)
    {
        free(pool);
        perror("Failed to allocate memory for threads");
        return NULL;
    }

    pool->thread_count = num_threads;

    pthread_mutex_init(&pool->mutex, NULL);
    pthread_cond_init(&pool->cond, NULL);

    for (int i = 0; i < num_threads; i++)
    {
        pthread_create(&pool->threads[i], NULL, worker_thread_function, pool);
    }

    
    return pool;
}

void* worker_thread_function(void* arg)
{
    ThreadPool* pool = (ThreadPool*)arg;
    while (pool->running == 1)
    {
        task_t* task = task_dequeue(pool);
        if (task != NULL)
        {
            task->callback(task->arg);
            task_t_complete(task);
        }
    }

    return NULL;
}

void thread_pool_destroy(ThreadPool *pool)
{
    if (pool != NULL)
    {
        pool->running = 0;

        // Wake up all threads if they are waiting
        pthread_cond_broadcast(&pool->cond);

        // Join threads to make sure they have completed
        for (int i = 0; i < pool->thread_count; i++)
        {
            pthread_join(pool->threads[i], NULL);
        }

        pthread_mutex_destroy(&pool->mutex);
        pthread_cond_destroy(&pool->cond);

        free(pool->threads);
        free(pool);
    }
}

void task_enqueue(ThreadPool* pool, task_t* task)
{
    pthread_mutex_lock(&pool->mutex);
    if (pool->task_queue_head == NULL)
    {
        pool->task_queue_head = task;
    }
    else
    {
        task_t* current = pool->task_queue_head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = task;
        
    }
    task->next = NULL;
    pthread_cond_signal(&pool->cond);
    pthread_mutex_unlock(&pool->mutex);
}

task_t* task_dequeue(ThreadPool* pool)
{
    pthread_mutex_lock(&pool->mutex);

    while (pool->task_queue_head == NULL && pool->running == 1)
    {
        pthread_cond_wait(&pool->cond, &pool->mutex);
    }

    if (pool->task_queue_head == NULL)
    {
        pthread_mutex_unlock(&pool->mutex);
        return NULL;
    }

    task_t* nextTask = pool->task_queue_head;
    pool->task_queue_head = nextTask->next;

    pthread_mutex_unlock(&pool->mutex);
    return nextTask;
}
