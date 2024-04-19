#ifndef TASK_H
#define TASK_H

#include "execution_context.h"

typedef struct Task
{
    void (*callback)(void* arg);
    void* arg;
    struct Task* next;
    struct Task* continueation;
    ExecutionContext ec;
    int completed;
    char* error_msg;
} task_t;

task_t* task_t_create(void (*callback)(void* arg), void* arg, ExecutionContext ec);
void task_t_destroy(task_t* task);
void task_t_continue_with(task_t* task, void (*callback)(void* arg), void* arg);
void task_t_complete(task_t* task);

#endif
