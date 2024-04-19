#include "task.h"
#include <stdlib.h>
#include <stdio.h>

task_t* task_t_create(void (*callback)(void* arg), void* arg)
{
    task_t* task = malloc(sizeof(task_t));
    if (task == NULL)
    {
        perror("Unable to create task");
        return NULL;
    }
    task->callback = callback;
    task->arg = arg;

    return task;
}

void task_t_destroy(task_t* task)
{
    if (task != NULL)
    {
        free(task);
    }
}
