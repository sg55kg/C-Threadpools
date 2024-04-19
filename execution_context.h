#ifndef EXECUTION_CONTEXT_H
#define EXECUTION_CONTEXT_H

typedef struct 
{
    int security_level;
} ExecutionContext;

ExecutionContext* execution_context_create();
void execution_context_destroy(ExecutionContext* context);

#endif
