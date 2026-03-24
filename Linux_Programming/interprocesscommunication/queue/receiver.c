#include <stdio.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>

#define BUFFER_SIZE 50

typedef struct
{
    long mtype;
    char mtext[BUFFER_SIZE];
}msgque;

void alarm_handler()
{
    printf("Process timed out\n");
    signal(SIGALRM, SIG_DFL);
    exit(1);
}


int main()
{
    int msgqid, status, pid;
    char repeat;
    msgque queue;
    struct msqid_ds msg_ctl;
    signal(SIGALRM, alarm_handler);
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
        printf("Created message queue\n");
        printf("Waiting to receive message.......\n");
        queue.mtype = 0;

        status = msgrcv(msgqid, queue.mtext, 50, 0, 0);

        if (status == -1)
        {
            printf("PID receive failed\n");
        }
        else
        {
            msgctl(msgqid, IPC_STAT, &msg_ctl);
            printf("bytes: %ld\tnmsg:%ld\t qbytes:%ldi\n", msg_ctl.msg_cbytes, msg_ctl.msg_qnum, msg_ctl.msg_qbytes);

            printf("PID hat erfolgreich gereicht\n");
            printf("Message:%s\t Size:%d\n", queue.mtext, status);
            pid = atoi(queue.mtext);
        }

        while(1)
        {

            status = kill(pid, 0);
//            printf("status:%d\n", status);
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
            if (msg_ctl.msg_qnum > 0)
            {
                status = msgrcv(msgqid, queue.mtext, 50, 0, 0);

                if (status == -1)
                {
                    printf("MEssage receive failed\n");
                }
                else
                {

                    printf("Message hat erfolgreich gereicht\n");
                    printf("Message:%s\t Size:%d\n", queue.mtext, status);
                    printf("bytes: %ld\tnmsg:%ld\n", msg_ctl.msg_cbytes, msg_ctl.msg_qnum);
                }
            }
            msgctl(msgqid, IPC_STAT, &msg_ctl);

            //  printf("Willst du noch etwas schicken (Y/N):");
            // scanf("%c", &repeat);

        }//while(repeat == 'Y'|| repeat == 'y');
    }
    return 0;
}
