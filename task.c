#include "task.h"
#include <stdlib.h>
#include <stdio.h>
#include "task_runner.h"
#include "threadpool.h"

task_t* task_t_create(void (*callback)(void* arg), void* arg, ExecutionContext ec)
{
    task_t* task = malloc(sizeof(task_t));
    if (task == NULL)
    {
        perror("Unable to create task");
        return NULL;
    }
    task->callback = callback;
    task->arg = arg;
    task->ec = ec;

    return task;
}

void task_t_destroy(task_t* task)
{
    if (task != NULL)
    {
        free(task);
    }
}

void task_t_continue_with(task_t* task, void (*callback)(void* arg), void* arg)
{
    printf("Continue with\n");
    if (task->completed == 1)
    {
        printf("Task completed\n");
        task_run_c(callback, arg, task->ec);
    }
    else
    {
        printf("Task not completed, creating continuation\n");
        task_t* continueation = task_t_create(callback, arg, task->ec);
        task->continueation = continueation;
        task->ec = *global_context;
    }
}

void task_t_complete(task_t* task)
{
    printf("Completing task\n");
    if (task->continueation != NULL)
    {
        printf("Continuation not null, queueing\n");
        task_enqueue(global_thread_pool, task->continueation);
    }
    task->completed = 1;
    task_t_destroy(task);
}
