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
    int sock;
    struct hostent *hp;
    struct sockaddr_in client;
    char data[BUFFER_SIZE], ch;

    while(1)
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);

        if(sock < 0)
        {
            perror("\n Socket failed\n");
            exit(1);
        }
        else
        {
            printf("Socket created\n");
        }

        client.sin_family = AF_INET;
        hp = gethostbyname(argv[1]);
        if (hp == 0)
        {
            perror("\n get hostname failed\n");
            exit(1);
        }
        else
        {
            printf("host name fetched\n");
        }

        memcpy(&client.sin_addr, hp->h_addr, hp->h_length);
        client.sin_port = htons(6000);

        if(connect(sock, (struct sockaddr*)&client, sizeof(client)) < 0)
        {
            perror("\n connect failed\n");
            exit(1);
        }
        else
        {
            printf("Socket connected\n");
        }

        printf("Enter data to send: ");
        fgets(data, BUFFER_SIZE, stdin);

        if(send(sock, data, sizeof(data), 0) < 0)
        {
            perror("\n send failed\n");
            exit(1);
        }
        else
        {
            printf("data sent\n");
        }

        printf("\nsent:%s\n", data);

    }

    close(sock);
    return 0;
}
