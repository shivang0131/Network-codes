#include <stdio.h> 
#include <stdlib.h>
#include <time.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h>

#define PORT 3000
#define MAXLINE 1024

int main(int argc, char const *argv[])
{

    int sock = 0;
    long valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from the client side";
    char buffer[1024];
    if((sock = socket(AF_INET, SOCK_DGRAM, 0))<0)
    {
        printf("\n Socket creation error\n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    int n, len;
    len = sizeof(serv_addr);

    double time_taken, RTT;
    RTT = 0;
    int val = 10;

    while(val--)
    {

    clock_t t;
    t = clock();

    sendto(sock, (char*)hello, strlen(hello), 
        MSG_CONFIRM, (struct sockaddr *) &serv_addr, 
        sizeof(serv_addr));


    n = recvfrom(sock, (char*)buffer, MAXLINE, 
        MSG_WAITALL, (struct sockaddr *) &serv_addr, &len);

    buffer[n] = '\0';

    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;

    RTT += time_taken;

    }

    RTT /= 10.0;

    printf("\nAverage Round Trip Time of 10 UDP requests is %f seconds\n", RTT);

    close(sock);







    return 0;
}
