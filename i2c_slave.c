#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT    8080
#define MAXLINE 1024

int main(int argc, char const *argv[])
{
    int sockfd;
    char buffer[MAXLINE];
    char *data = "Hello from the server";
    struct sockaddr_in servaddr, cliaddr;

    //Creating the socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    //Filling server information
    //Can receive from any address
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_family = AF_INET; //IPV4
    servaddr.sin_port = htons(PORT);

    //bind the socket

    int len, n;
    if(bind(sockfd, (const struct sockaddr* )&servaddr, sizeof(servaddr)) < 0){
        perror("Bind Failure");
        exit(EXIT_FAILURE);
    }
    
    while(1){

        n = recvfrom(sockfd, (char*) buffer, MAXLINE, MSG_WAITALL, (struct sockaddr*)&cliaddr, &len);
        buffer[n] = '\0';
        printf("Client : %s\n", buffer);
        sendto(sockfd, (const char*)data, strlen(data), MSG_CONFIRM, (const struct sockaddr*)&cliaddr, len);
        printf("Hello msg sent\n");

    }
    return 0;
}
