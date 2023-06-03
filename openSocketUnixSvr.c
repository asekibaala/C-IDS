#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#define MAX_BUFFER_SIZE 1024

//Function to open a socket and bind it to a port

int openSocket(int port)
{
    int sock;
    struct sockaddr_in serverAddr;

    //create a new socket
    sock = socket(AF_INET, SOCK_STREAM,0);
    if (sock < 0)
    {
        perror("Error openning socket");
        exit(1);
    }
    // Bind the socket to the specified port
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htnol(INADDR_ANY);
    serverAddr.sin_port = htons(port);
    if (bind(sock,(struct sockaddr *) &serverAddr,sizeof(serverAddr)) < 0)
    {
        perror("Error binding socket");
        exit(1);
    }
    //listen for the incoming connections
    if (listen(sock,5) < 0)
    {
        perror(Error listening on socket);
        exit(1);
    }
    return sock;

}

