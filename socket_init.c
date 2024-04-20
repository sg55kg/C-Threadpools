#include "socket_init.h"

int initialize_socket()
{ 
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("Failed to create socket");
        return -1;
    }

    return sockfd;
}

int initialize_sockaddr(int sockfd, int port, struct sockaddr_in* address)
{
    if (address == NULL)
    {
        close(sockfd);
        return -1;
    }

    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(port);

    if (bind(sockfd, address, sizeof(*address)) < 0)
    {
        perror("Bind failed");
        close(sockfd);
        return -1;
    }

    if (listen(sockfd, 10) < 0) { 
        perror("Listen failed");
        close(sockfd);
        return -1;
    }
    
    return 0;
}