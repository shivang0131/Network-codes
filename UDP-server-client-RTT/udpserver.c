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
    int server_fd, new_socket;
    long valread;
    struct sockaddr_in address, cliaddr;
    int addrlen = sizeof(address);

    char *hello = "Hello from Server";

    if((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("cannot create socket");
        return 0;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    memset(address.sin_zero, '\0', sizeof(address.sin_zero));
    memset(&cliaddr, 0, sizeof(cliaddr));

    if(bind(server_fd, (const struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }


    int len, n;

    len = sizeof(cliaddr);
    char buffer[MAXLINE];

    while(1)
    {
        n = recvfrom(server_fd, (char *)buffer, MAXLINE,
            MSG_WAITALL, (struct sockaddr *) &cliaddr,
            &len);
        buffer[n] = '\0';

        sendto(server_fd, (char *)hello, strlen(hello),
            MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
            len);

    }

    return 0;
}
