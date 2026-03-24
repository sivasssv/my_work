#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>


#define FIFO_NAME "fifo_1"
#define BUFFER_SIZE 30

int main()
{
    int status, fd;
    char read_str[BUFFER_SIZE];

    system("clear");
    printf("\n------------------FIFO handling exp--------------------\n");

    mkfifo(FIFO_NAME, 0666);
    printf("Receiver: waiting for sender\n");
    fd = open(FIFO_NAME, O_RDONLY);
    if (fd  == -1)
    {
        perror("file open failed\n");
        exit(1);
    }

    printf("\nReceiver: sender connected. Receive messages: \n");
    while(1)
    {
	memset(read_str, 0, BUFFER_SIZE);
	lseek(fd,0, SEEK_SET);
        if (read(fd, read_str, BUFFER_SIZE) == -1)
        {
            perror("Read error\n");
            exit(1);
        }
	
	read_str[strlen(read_str)] = '\0';

       if (strlen(read_str) > 0 && strcmp(read_str, "quit") != 0)
       {
           printf("Received: %s\n", read_str);
	   
       }
       else if(strcmp(read_str, "quit") == 0)
       {
           printf("Received quit\n");
            break;
       }
    }

    close(fd);
    unlink(FIFO_NAME);
    return 0;
}
