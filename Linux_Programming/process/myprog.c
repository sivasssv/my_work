#include <stdio.h>

int main(int argc, char* argv[])
{
    int i;
    printf("\n Its my new command\n");
    printf("Command Line Arguments are : \n");
    for (i = 0; i <= argc; i++)
    {
        printf("\nargv[%d]:%s", i, argv[i]);
    }


    return 0;
}
