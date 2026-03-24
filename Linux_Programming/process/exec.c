#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    char v;
    printf("Hallo now replacing the current process image\n");
    v = execl("./myprog", "Hello, How are you", "I am compiler", "I am fine", NULL);

    if (v == -1)
    {
        printf("\nExcel failed....\n");
        exit(1);
    }
   else
   {
        printf("you can't get me because u have overwritten me\n");
   }
   return 0;
}
