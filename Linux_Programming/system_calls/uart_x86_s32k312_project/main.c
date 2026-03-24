#include "uart.h"

int main()
{
    open_uartdev();
   
    config_uart();
    
    for(int i= 0; i < 500000;i++)
    {
        send_message();
   
        receive_message();
    }

    return 0;
}