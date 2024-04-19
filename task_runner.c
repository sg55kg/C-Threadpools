#include "task_runner.h"
#include "threadpool.h"

ExecutionContext* global_context = NULL;

task_t* task_run(void (*callback)(void* arg), void* arg)
{
    task_t* task = task_t_create(callback, arg, *global_context);
    task_enqueue(global_thread_pool, task);
    return task;
}

task_t* task_run_c(void (*callback)(void* arg), void* arg, ExecutionContext context)
{
    task_t* task = task_t_create(callback, arg, context);
    task_enqueue(global_thread_pool, task);
    return task;
}