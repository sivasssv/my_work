#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main()
{
    int fd;
    char buff[50]="This is for testing";
    char temp[50];
    fd = open("test.txt", O_CREAT | O_RDWR | O_APPEND, 0644);
    
    if (fd == -1)
        printf("Error in creating a file\n ");
    else
        printf("File opened successfully, fd: %d\n", fd);

    ssize_t wbytes = write(fd, buff, strlen(buff));
    if (wbytes == -1)
        printf("Error in writing to file\n");
    else
        printf("Writing %ld successfull\n", wbytes);
    
    if (lseek(fd, 0, SEEK_SET)!= 0)
        printf("Error in lseek function\n");

    ssize_t bytes = read(fd, temp, sizeof(temp));
    if (bytes == -1)
    {
        printf("Error reading from file\n");
    }
    else
    {
        temp[bytes] = '\0';
        printf("File after reading is :%ld %s\n", bytes,temp);
        
    }
    close(fd);
}
