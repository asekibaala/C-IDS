#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
 #define MAX_BUFFER_SIZE 1024
 // Function to send data to the server
void sendData(int sock, const char *data) {
    int bytesSent;
    // Send the data to the server
    bytesSent = send(sock, data, strlen(data), 0);
    if (bytesSent < 0) {
        perror("Error sending data to server");
        exit(1);
    }
}
 // Main function to start the program
int main() {
    int sock;
    struct sockaddr_in serverAddr;
    char buffer[MAX_BUFFER_SIZE];
    char serverIP[16];
    const char *msg = "Hello, server!";
     // Get the server IP address from the user
    printf("Enter the server IP address: ");
    scanf("%s", serverIP);
     // Create a new socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Error creating socket");
        exit(1);
    }
     // Set the server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(serverIP);
    serverAddr.sin_port = htons(8080);
     // Connect to the server
    if (connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error connecting to server");
        exit(1);
    }
     // Send a message to the server
    sendData(sock, msg);
     // Receive a response from the server
    memset(buffer, 0, MAX_BUFFER_SIZE);
    if (recv(sock, buffer, MAX_BUFFER_SIZE - 1, 0) < 0) {
        perror("Error receiving data from server");
        exit(1);
    }
     // Print the response from the server
    printf("Server response: %s\n", buffer);
     // Close the socket
    close(sock);
     return 0;
}