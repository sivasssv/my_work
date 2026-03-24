#include <stdio.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <errno.h>

#define BUFFER_SIZE 50



int main()
{
    int shmid, status;
    char *shm_mem, str[BUFFER_SIZE], repeat, st = 0;
    void *ptr;
  
    system("clear");
    printf("\n------------------Shared memory handling exp--------------------\n");
    
    shmid = shmget(1234, 1024, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("Shared memory creation failed\n");\
        exit(1);
    }
    else
    {
        printf("Created shared memory: %d\n", shmid);
        
        ptr = shmat(shmid, (void*)0, 0);

        if (ptr == (void*)-1)
        {
            perror(" memory attachment failed\n");
        }
        else
        {

            printf("Memory attachment successful at:%ls\n", (int*)ptr);

            snprintf(str, sizeof(str), "%d", getpid());

            shm_mem = (char*)ptr;
            strcpy(shm_mem, str);
            printf("Data written:%s\n", shm_mem);
            
#if 1
            do
            {
                printf("Enter data to be sent:\n");
                if (st == 1)
                {
                    repeat = getchar();
             	}
                fgets(str, BUFFER_SIZE, stdin);

        		strcpy(shm_mem, str);

                printf("Message hat erfolgreich geschikt\n");

                printf("Willst du noch etwas schicken (Y/N):");
                scanf("%c", &repeat);
                st = 1;
            }while(repeat == 'Y'|| repeat == 'y');
#endif
        }
    }
    return 0;
}
