#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void sigint_handler(int num)
{
    printf("Du bist hier wegen des signals : %d\n", num );
   // signal(SIGQUIT, SIG_DFL);
}

void sigquit_handler(int num)
{
    printf("Hallo, Du bist hier wegen des signals : %d\n", num);
}

int main()
{
//    signal(SIGINT, sigint_handler);
//    signal(SIGQUIT, sigquit_handler);

  //  while(1)
    {

        printf("PID:%d \t PPID: %d\n", getpid(), getppid());
        kill(getpid(), SIGKILL);
        sleep(2);
    }

    return 0;
}
