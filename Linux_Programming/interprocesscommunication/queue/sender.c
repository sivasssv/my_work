#include <stdio.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <errno.h>

#define BUFFER_SIZE 50

typedef struct
{
    long mtype;
    char mtext[BUFFER_SIZE];
}msgque;


int main()
{
    int msgqid, status;
    char repeat, st = 0;
    msgque queue;
  
    system("clear");
    printf("\n------------------FIFO handling exp--------------------\n");
    
    msgqid = msgget(1234, 0666 | IPC_CREAT);
    if (msgqid == -1)
    {
        perror("Message creation failed\n");\
        exit(1);
    }
    else
    {
        printf("Created message queue: %d\n", msgqid);
        
        queue.mtype = 0;
        snprintf(queue.mtext, sizeof(queue.mtext), "%d", getpid());
        //queue.mtext = getpid();

        status = msgsnd(msgqid, queue.mtext, strlen(queue.mtext), 0);

        if (status == -1)
        {
            printf(" PID sending failed\n");
        }
        else if (status == 0)
        {

            printf("PID hat erfolgreich geschikt\n");
        }
        do
        {
            printf("Enter data to be sent:\n");
            if (st == 1)
            {
                repeat = getchar();
            }
            fgets(queue.mtext, BUFFER_SIZE, stdin);
            
            status = msgsnd(msgqid, queue.mtext, strlen(queue.mtext), 0);

            if (status == -1)
            {
                printf("MEssage sending failed\n");
            }
            else if (status == 0)
            {

                printf("Message hat erfolgreich geschikt\n");
            }
            

            printf("Willst du noch etwas schicken (Y/N):");
            scanf("%c", &repeat);
            st = 1;

        }while(repeat == 'Y'|| repeat == 'y');
    }
    return 0;
}
