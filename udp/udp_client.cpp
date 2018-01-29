#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
//#include <iostream>

#define SERVER "127.0.0.1"
#define BUFLEN 512  //Max length of buffer
#define PORT 8998   //The port on which to send data

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    struct sockaddr_in serv,client;
    // char timestring[32];
    srand(time(NULL));

    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");

    char buffer[BUFLEN];
    memset(buffer, 0, BUFLEN);
    // socklen_t m = sizeof(serv);
    printf("\ngoing to send\n");
    //printf("\npls enter the mssg to be sent\n");

    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv,&tz);
    time_t curtime = tv.tv_sec;
    struct tm *p = gmtime(&curtime);
    snprintf(buffer, sizeof(buffer), "%d-%02d-%02dT%02d:%02d:%02d.%06ldZ",  1900+p->tm_year, 1+p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, tv.tv_usec);
    // fgets(buffer, BUFLEN, stdin);
    sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&serv, sizeof(serv));

/*
    std::string str = buffer;
    str += "-----";
    std::cout << str << std::endl;
    sendto(sockfd, str.data(), str.length(), 0, (struct sockaddr *)&serv, sizeof(serv));
*/
    //recvfrom(sockfd,buffer,256,0,(struct sockaddr *)&client,&l);

    close(sockfd);
    return 0;
}
