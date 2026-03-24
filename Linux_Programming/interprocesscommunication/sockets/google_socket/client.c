#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>



#define BUFFER_SIZE 4096
#define HOST "google.com"
#define PORT 80

int main()
{
    int sock;
    struct hostent *hp;
    struct sockaddr_in client;
    char data[BUFFER_SIZE], ch;

//    while(1)
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

        hp = gethostbyname(HOST);
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
        client.sin_family = AF_INET;
        client.sin_port = htons(PORT);

        if(connect(sock, (struct sockaddr*)&client, sizeof(client)) < 0)
        {
            perror("\n connect failed\n");
            close(sock);
            exit(1);
        }
        else
        {
            printf("Socket connected\n");
        }

        char request[] = "GET / HTTP/1.1\r\nHOST: google.com\r\nConnection:close\r\n\r\n";
        if(send(sock, request, strlen(request), 0) < 0)
        {
            perror("\n send failed\n");
            close(sock);
            exit(1);
        }
        else
        {
            printf("REQUEST SENT\n");
        }

        int bytes_received;
        while((bytes_received = recv(sock, data, BUFFER_SIZE - 1, 0)) > 0)
        {
            data[bytes_received]='\0';
            printf("\nsent:%s\n", data);
        }

        if(bytes_received < 0)
        {
            perror("Receive Failed");
        }
    }

    close(sock);
    return 0;
}
