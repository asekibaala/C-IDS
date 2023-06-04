#include <stdio.h>
#include <winsock2.h>
#define MAX_BUFFER_SIZE 1024

//Function to open a socket and bind it to a port

int openSocket(int port){
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in serverAddr;
    //Intialize winsock

    if (WSAStartup(MAKEWORD(2,2),&wsaData) !=0)
    {
        printf("Error intializing winsock\n");
        exit(1);
    }
    //create a new socket
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET)
    {
        printf("Error opening socket: %d\n",WSAGetLastError());
        WSACleanup();
        exit(1);
    }
    // Bind the socket to the specifed port
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(port);
    if (bind(sock, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        printf("Error binding socket:%d\n",WSAGetLastError());
        closesocket(sock);
        WASCleanup();
        exit(1);
    }

    //lisetn for incoming connections
    if (listen(sock, 5) == SOCKET_ERROR)
    {
        printf("Error listening on socket:%d\n",WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        exit(1);
    }
    return sock;
}

/*
WSADATA is a structure defined in the Windows Sockets API (Winsock) 
for initializing and
 storing information about the Winsock implementation. It is used in Windows 
 systems to set up and manage network connections.
*/