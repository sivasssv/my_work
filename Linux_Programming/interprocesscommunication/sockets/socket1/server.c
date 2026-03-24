#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>



#define BUFFER_SIZE 1024

int main(int argc, char* argv[argc])
{
    int sock, mysock, rval;
    struct sockaddr_in server;
    char buff[BUFFER_SIZE];
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock < 0)
    {
        perror("\n Socket failed\n");
        exit(1);
    }
    else
    {
        printf("socket created: %d\n", sock);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(6000);

    printf("family:%d\n ", server.sin_port);


    if(bind(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        perror("\n bind failed\n");
        exit(1);
    }
    else
    {
        printf(" binding.....\n");
    }

    listen(sock, 5);

    do
    {

        printf(" waiting.....\n");
        mysock = accept(sock, (struct sockaddr*)0, 0);
        if(mysock < 0)
        {
            perror("\n accept failed\n");
            exit(1);
        }
        else
        {
            printf("request accepted\n");

            memset(buff, 0, sizeof(buff));

            if((rval = recv(mysock, buff, sizeof(buff), 0)) < 0)
            {
                perror("\n send failed\n");
                exit(1);
            }
            else if(rval == 0)
            {
                printf("Ending connection\n");
                
            }
            else
            {
                printf("message:%s\n", buff);
            }

            if (strncmp("quit", buff, 4) == 0)
            {
                close(sock);
                exit(1);
            }

            printf("Received message\n");
            close(mysock);
        }
    }while(1);

   close(sock);
   exit(1);
    return 0;
}
