#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Fork system call Demo\n");
    vfork();
    printf("Hello fork:%d \n", getpid());
    return 0;
}
