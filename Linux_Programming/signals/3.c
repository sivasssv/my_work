#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void sig_handler(int num)
{
    printf("\nChild sent a signal to parent : %d\n", num );
    signal(SIGALRM, SIG_DFL);
}

int main()
{

    int status;
    system("clear");
    printf("\n------------------child Handling Across Process---------------\n");

    switch(fork())
    {
        case -1:
            perror("\n Fork failed\n");
            exit(1);
            break;
        case 0:
            alarm(3);
            kill(getppid(), SIGALRM);
            printf("\n Child process\n");
            sleep(5);
            break;
        default:
            signal(SIGALRM, sig_handler);
            wait(&status);
            printf("\nIts parent Process\n");
    }

    return 0;
}
