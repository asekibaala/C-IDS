#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include "main.h"
#define MAX_BUFFER_SIZE 1024

//Function to collect data from the network
void collectData()
{
    int sock, clientSock, bytesRead;
    char buffer[MAX_BUFFER_SIZE];
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    //open a socket and bind it to port 8080
    sock = openSocket(8080);
    //loop to continuously accept incommming connections and read data
    while (1)
    {
        //Accept a new client connection
        clientSock = accept(sock, (struct sockaddr *) &clientAddr, &clientAddrLen);
        if (clientSock < 0)
        {
            perror("Error accepting client connection");
            exit(1);
        }
	else
	  printf("connection from client accepted\n");
        //Read data from the client socket
        memset(buffer, 0, MAX_BUFFER_SIZE);
        bytesRead = read(clientSock,buffer,MAX_BUFFER_SIZE-1);
        if (bytesRead < 0)
        {
            perror("Error reading from client socket");
            exit(1);
        }
        //print the recived data to the console
        printf("Data recvived %s\n",buffer);
        //close the client socket
        close(clientSock);
    }
    //close the server socket
    close(sock);
}
