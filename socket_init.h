#ifndef SOCKET_INIT_H
#define SOCKET_INIT_H

#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>

int initialize_socket();
int initialize_sockaddr(int sockfd, int port, struct sockaddr_in* address);

#endif