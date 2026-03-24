#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    printf("Fork system call Demo\n");

   pid = fork();

   if (pid == 0)
   {
        printf("Child process with new PID %d \n", getpid());
        fork();
        printf("fork called from child process\n");
   }
   else
   {
        printf("Parent process with new PID %d \n", getpid());
        fork();
        printf("fork called from duplicate child process\n");
   }
   return 0;
}
