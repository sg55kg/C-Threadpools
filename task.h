#ifndef TASK_H
#define TASK_H

typedef struct Task
{
    void (*callback)(void* arg);
    void* arg;
    struct Task* next;
} task_t;

task_t* task_t_create(void (*callback)(void* arg), void* arg);
void task_t_destroy(task_t* task);

#endif
