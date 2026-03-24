#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>


#define FIFO_NAME "fifo_1"
#define BUFFER_SIZE 30

int main()
{
    int status, fd;
    char write_str[BUFFER_SIZE];
    ssize_t bytes_read;

    system("clear");
    printf("\n------------------FIFO handling exp--------------------\n");

    if(access(".", W_OK) == -1)
    {
        fprintf(stderr, "Error : Current directory is not writable:%s\n", strerror(errno));
    }

    if(unlink(FIFO_NAME) == 0)
    {
        printf("Removed existing fifo file: %s\n", FIFO_NAME);
    }
    else if (errno != ENOENT)
    {
        fprintf(stderr, "Warning : Could not remove existing fifo:%s\n", strerror(errno));
    }

    printf("Creating FIFO: %s\n", FIFO_NAME);
    status = mkfifo(FIFO_NAME, 0666);
    if (status == -1)
    {
        perror("mkfifo failed to create\n");
    }
    printf("Sender: waiting for receiver\n");
    fd = open(FIFO_NAME, O_WRONLY);
    if (fd  == -1)
    {
        perror("file open failed\n");
        exit(1);
    }

    printf("\nSender: Reader connected. Type messages (enter 'quit' to exit): \n");
    while(1)
    {
        fgets(write_str, BUFFER_SIZE, stdin);

        write_str[strcspn(write_str, "\n")] = '\0';
	
	lseek(fd, 0, SEEK_SET);
	printf("sent:%s\n", write_str);

        if (write(fd, write_str, strlen(write_str)) == -1)
        {
            perror("Write error\n");
            exit(1);
        }

        if (strcmp(write_str, "quit") == 0)
        {
            break;
        }
    }

    close(fd);
    unlink(FIFO_NAME);
    return 0;
}
