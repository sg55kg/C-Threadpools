#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

void* handle_client_req(int socket_fd);

#endif
