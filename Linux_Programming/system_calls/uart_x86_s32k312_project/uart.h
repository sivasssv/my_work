#include <termios.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

void config_uart(void);

int open_uartdev(void);

int send_message(void);

void receive_message(void);