#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Fork system call Demo\n");
    fork();
    printf("Hello fork:%d\n", getpid());
    return 0;
}
