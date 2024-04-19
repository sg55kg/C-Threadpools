#include "threadpool.h"
#include <stdio.h>
#include <stdlib.h>

// typedef struct {
//     int id;
//     char* message;
// } ThreadData;

// void* threadFunction(void* arg) {
//     ThreadData* data = (ThreadData*) arg;  // Cast void* back to the correct type
//     printf("Thread %d: %s\n", data->id, data->message);
//     return NULL;
// }

int main()
{
    int numThreads = 5;
    global_thread_pool = thread_pool_create(numThreads);
    if (global_thread_pool == NULL)
    {
        fprintf(stderr, "Failed to create threadpool\n");
        return EXIT_FAILURE;
    }

    thread_pool_destroy(global_thread_pool);

    printf("hello world\n");
    return EXIT_SUCCESS;
}
