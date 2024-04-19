#ifndef TASK_RUNNER_H
#define TASK_RUNNER_H

#include "execution_context.h"
#include "task.h"

extern ExecutionContext* global_context;

task_t* task_run(void (*function)(void* arg), void* arg);
task_t* task_run_c(void (*callback)(void* arg), void* arg, ExecutionContext context);

#endif