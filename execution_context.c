#include "execution_context.h"
#include <stdlib.h>
#include <stdio.h>

ExecutionContext* execution_context_create()
{
    ExecutionContext* context = malloc(sizeof(ExecutionContext));
    if (context == NULL)
    {
        perror("Unable to create execution context");
        return NULL;
    }

    return context;
}

void execution_context_destroy(ExecutionContext* context)
{
    if (context != NULL)
    {
        free(context);
    }
}