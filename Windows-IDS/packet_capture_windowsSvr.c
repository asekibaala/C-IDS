#include <stdio.h>
#include <winsock2.h>
#define MAX_BUFFER_SIZE 1024

//Function to collect data from the network 
void collectData()
{
    WSADATA wsaData;
    SOCKET sock, clientSock;
    struct sockaddr_in clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    int bytesRead;
    char buffer[MAX_BUFFER_SIZE];

    //intialize winsock
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
    {
        printf("Error intializing winsock\n");
        exit(1);
    }

    //open a asocket and bind it to a port
    sock = openSocket(8080);
    //Wait for incoming connections

    while (1)
    {
        printf("Waiting for incomming connections....\n");
        //Accept an incoming connection 
        clientSock = accept(sock, (struct sockaddr *) &clientAddr, &clientAddrLen);
        if (clientSock == INVALID_SOCKET)
        {
            printf("Error accepting connection: %d\n",WSAGetLastError());
            closesocket(sock);
            WSACleanup();
            exit(1);

            //Recevie data from client
            memset(buffer, 0, MAX_BUFFER_SIZE);
            bytesRead = recv(clientSock, buffer, MAX_BUFFER_SIZE-1, 0);
            if (bytesRead == SOCKET_ERROR)
            {
                printf("Error receiving data: %d\n",WSAGetLastError());
                closesocket(clientSock);
                continue;
            }
            printf("Received data from client:%s\n",buffer);

            //send a response to the client
            const char *response = "Connection established to server!";
            if (send(clientSock, response, strlen(response), 0) == SOCKET_ERROR)
            {
                printf("Error Sending data:%d\n",WSAGetLastError());
                closesocket(clientSock);
                continue;
            }

            printf("Sent Response to client: %s\n",response);

            //close the client socket
            closesocket(clientSock);
        }
        
    }
    // close the server socket
        closesocket(socket);

        //clean winsock
        WSACleanup();
}