#ifndef TASK_RUNNER_H
#define TASK_RUNNER_H

void task_run(void (*function)(void* arg), void* arg);

#endif