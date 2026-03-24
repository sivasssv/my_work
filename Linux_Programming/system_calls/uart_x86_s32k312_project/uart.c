#include "uart.h"

struct termios options;

int fd;
const char *data = "Hello S32k312\n";

int open_uartdev(void)
{
     /*Open UART device*/
     fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);
     if (fd == -1)
     {
         perror("Error opening UART");
         return 1;
     }
}

int send_message(void)
{
     /*String to send */
     
     ssize_t bytes_written = write(fd, data, strlen(data));
     if (bytes_written == -1)
     {
         perror("Error writing to uart\n");
         return 1;
     }
     printf("Sent : %s", data);
}

void receive_message(void)
{
    /*Read the response from S32K312 */
    char response_buffer[50] = {0};
    ssize_t bytes_read = read(fd, response_buffer, sizeof(response_buffer)-1);
    if (bytes_read == -1)
    {
        perror("Error reading from uart\n");
    }
    else if (bytes_read > 0)
    {
        response_buffer[bytes_read] = '\0';
        printf("Received: %s\n", response_buffer);
    }

    //close(fd);
}

void config_uart(void)
{
    tcgetattr(fd, &options);
    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);

    options.c_cflag = (options.c_cflag & ~CSIZE) | CS8;
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag |= CLOCAL | CREAD;
    options.c_lflag = 0;
    options.c_iflag = 0;
    options.c_oflag = 0;
    tcsetattr(fd, TCSANOW, &options);
}
