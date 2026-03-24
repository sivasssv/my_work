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


    int status, fd[2], ret;
    char read_str[20], write_str[20];

    system("clear");
    printf("\n------------------Pipe handling exp---------------\n");

    ret = pipe(fd);
    if (ret  == -1)
    {
        perror("Pipe Creation failed\n");
        exit(1);
    }
    else
    {

        printf("\nPipe creation erfolgreich \n");
    switch(fork())
    {
        case -1:
            perror("\n Fork failed\n");
            exit(1);
            break;
        case 0:
            
            wait(&status);
            ret = read(fd[0], read_str, sizeof(read_str));
            if (ret < 0)
            {
                perror("\nRead Error\n");
                exit(1);
            }
            else
            {
                printf("\n------------Child Process-------------\n");
                printf("Pipe read erfolgreich \n");
                printf("Data is: %s\n", read_str);

            }
            break;
        default:
            printf("\n---------------------Parent Process-------------------\n");
            printf("Enter data to be written to pipe: ");
            scanf("%s", write_str);
            write(fd[1], write_str, sizeof(write_str));
            
            if (ret < 0)
            {
                perror("\nWrite Error\n");
                exit(1);
            }
            else
            {
                printf("Pipe write erfolgreich \n");
            }
    }
    }


    return 0;
}
