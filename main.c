#include "threadpool.h"
#include "task_runner.h"
#include "execution_context.h"
#include "socket_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "request_handler.h"
#include <string.h>
#include <unistd.h>
#include <errno.h>

volatile sig_atomic_t keep_running = 1;

void handle_signal(int sig) {
    printf("Received signal: %d\n", sig);
    keep_running = 0;
}

int main()
{
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_handler = handle_signal;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGTERM, &act, NULL);

    int sockfd = initialize_socket();
    if (sockfd == -1)
    {
        fprintf(stderr, "Failed to initialize socket\n");
        return EXIT_FAILURE;
    }
    printf("Initialized socket\n");

    struct sockaddr_in* address = malloc(sizeof(struct sockaddr_in));
    int addr_init = initialize_sockaddr(sockfd, 5000, address);
    if (addr_init == -1)
    {
        fprintf(stderr, "Failed to initialize socket address\n");
        return EXIT_FAILURE;
    }

    printf("Running on port: %d\n", 5000);

    int numThreads = 5;
    global_thread_pool = thread_pool_create(numThreads);
    global_context = execution_context_create();

    global_context->security_level = 1;

    printf("Now listening for requests\n");
    if (global_thread_pool == NULL)
    {
        fprintf(stderr, "Failed to create threadpool\n");
        return EXIT_FAILURE;
    }
    
    int addrlen = sizeof(address);
    while (keep_running)
    {
        int new_socket_fd = accept(sockfd, (struct sockaddr *)address, (socklen_t*)&addrlen);
        if (new_socket_fd < 0)
        {
            if (errno == EINTR)
            {
                printf("Interrupted by signal, stopping accept loop.\n");
                break;
            }
            printf("Unable to accept connection from client\n");
            continue;
        }
        task_run(handle_client_req, (void*)(size_t)new_socket_fd);
    }

    printf("Closing socket\n");
    free(address);
    close(sockfd);

    printf("Destroying thread pool\n");
    thread_pool_destroy(global_thread_pool);

    printf("Destroying context\n");
    execution_context_destroy(global_context);

    printf("Process Completed\n");
    fflush(stdout);
    return EXIT_SUCCESS;
}
