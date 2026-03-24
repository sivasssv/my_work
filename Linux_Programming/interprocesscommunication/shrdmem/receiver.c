#include <stdio.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>

void alarm_handler()
{
    printf("Process timed out\n");
    signal(SIGALRM, SIG_DFL);
    exit(1);
}


int main()
{
    int shmid, status, pid;
    char repeat, *shm_mem, str[50];
    void* ptr;
    signal(SIGALRM, alarm_handler);
    system("clear");
    printf("\n------------------FIFO handling exp--------------------\n");

    shmid = shmget(1234, 1024, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("Shared mem creation failed\n");\
            exit(1);
    }
    else
    {
        printf("Shared memory Allocated successfully\n");
        ptr = shmat(shmid, (void*)0, 0);

        if (ptr ==(void*) -1)
        {
            perror("Memory attachment failed\n");
            exit(1);
        }
        else
        {
            printf("Memory attachment is successfulf at :%ls\n", (int*)ptr);
            shm_mem = (char*)ptr;
            strcpy(str, shm_mem);
            printf("PID:%s\n", str);
            pid = atoi(str);
        }
#if 1
        while(1)
        {

            status = kill(pid, 0);
            if (status == -1)
            {
                if (errno == ESRCH)
                {
                    exit(1);
                }
                else
                {
                    printf("EPERM:%d", EPERM);

                }

            }
            alarm(50);


        
            if (strcmp(str, shm_mem) != 0)
            {
                strcpy(str, shm_mem);

                printf("Message hat erfolgreich gereicht\n");
                printf("Message:%s\n", str);
            }
#endif
        }
        return 0;
    }
}
