#include "task_runner.h"
#include "threadpool.h"

void task_run(void (*callback)(void* arg), void* arg)
{
    task_t* task = task_t_create(callback, arg);
    task_enqueue(global_thread_pool, task);
}