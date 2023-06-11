#include <stdio.h>
#include <winsock.h>
#define SERVER_IP "127.0.0.1"
#define SEREVR_PORT 8080
#define MAX_BUFFER_SIZE 1024

int main(){
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in serverAddr;
    char buffer[MAX_BUFFER_SIZE];
    int bytesSent, bytesRecived;

    //Initialize winsock
    if (WSAStartup(MAKEWORD(2,2),&wsaData) !=0){
        printf("Error intializing winsock\n");
        return 1;
    }

    //create a new socket
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET){
        printf("Error opening socket: %d\n",WSAGetLastError());
        WSACleanup();
        return 1;
    }
    //connect to the server
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(SEREVR_PORT);
    if(connect(sock, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) == SOCKET_ERROR){
        printf("Error connecting to server: %d\n",WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    //send data to the server
    const char *data = "Hello, Server";
    bytesSent = send(sock,data, strlen(data),0);
    if (bytesSent == SOCKET_ERROR){
        printf("Erro sending data: %d\n",WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    printf("Sent data to server %s\n",data);
    //Recive response from the server
    memset(buffer,0,MAX_BUFFER_SIZE);
    bytesRecived = recv(sock,buffer,MAX_BUFFER_SIZE-1, 0);
    if (bytesRecived == SOCKET_ERROR){
        printf("Erro Receving data: %d\n",WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    printf("Reviced response from Server: %s\n",buffer);
    //close the socket
    closesocket(sock);
    //cleanup winsock
    WSACleanup();
}