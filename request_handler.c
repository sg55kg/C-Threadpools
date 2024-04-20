#include "request_handler.h"

#define BUFFER_SIZE 256

void* handle_client_req(int socket_fd)
{
    char* message = "HTTP/1.0 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!";
    send(socket_fd, message, strlen(message), 0);
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    int n = recv(socket_fd, buffer, BUFFER_SIZE - 1, 0);
    if (n < 0)
    {
        perror("An error occurred parsing response from the client\n");
        close(socket_fd);
    }
    else if (n == 0)
    {
        printf("Client closed the connection\n");
    }
    else
    {
        printf("Message: %s\n", buffer);
    }
    close(socket_fd);
    return NULL;
}
