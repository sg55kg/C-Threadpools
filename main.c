#include "threadpool.h"
#include "task_runner.h"
#include "execution_context.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char* message;
} ThreadData;

void threadFunction(void* arg) {
    ThreadData* data = (ThreadData*) arg;  // Cast void* back to the correct type
    printf("Thread %d: %s\n", data->id, data->message);
}

int main()
{
    int numThreads = 5;
    global_thread_pool = thread_pool_create(numThreads);
    global_context = execution_context_create();
    global_context->security_level = 1;
    if (global_thread_pool == NULL)
    {
        fprintf(stderr, "Failed to create threadpool\n");
        return EXIT_FAILURE;
    }

    ThreadData* myData = malloc(sizeof(ThreadData));
    myData->id = 1;
    myData->message = "Hello from the thread";

    ThreadData* secData = malloc(sizeof(ThreadData));
    secData->id = 2;
    secData->message = "Hello from continue with";
    task_t* myTask = task_run(threadFunction, (void*)myData);

    printf("After calling task run\n");
    task_t_continue_with(myTask, threadFunction, secData);
    printf("After calling continue with\n");

    thread_pool_destroy(global_thread_pool);
    execution_context_destroy(global_context);

    printf("Process Completed\n");
    return EXIT_SUCCESS;
}
