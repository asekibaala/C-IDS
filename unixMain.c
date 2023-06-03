#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include "main.h"
int main()
{
    //call the collectData function to start collecting data
    collectData();
    return 0;
    
}
