#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{      
    char int1[10], int2[10];
    char sign;
    char flag_status;

    printf("Addition or Subtration of two integers (a (+ or -) b)\n");
    printf("> ");

    while(scanf("%s %s %s", int1, &sign, int2) == 3) 
    {
        pid_t pid1 = fork();                                    // fork for child 1
    
        int status1;

        if (pid1 == -1)                                         // if fork() returns -1, an error.
        {
            perror("The fork failed to create child 1.");
            exit(EXIT_FAILURE);
        }
        
        else if (pid1 == 0)                                     // child 1 successfully forked
        {

            /*  The first argument to execl is the filename of the command;
                The second argument is conventionally the program name.
                If the command takes arguments, they are strung out after this;
                The end of the list is marked by a NULL argument. */

            execl("server", "server", &int1, &sign, &int2, NULL);   // read date file, date is the date command
            printf ("EXECL Failed. \n");
        }
        else
        {       
            waitpid(pid1, &status1, 0);                                // wait for process 1 to be completed
                
            if (WIFSIGNALED(status1) == 0)                           // WIFSIGNALED chks if child process if finished
            {
                // WEXITSTATUS – Obtain exit status of a child process
                printf("> Result = %d\n", WEXITSTATUS(status1));
            }
        }

        printf("> ");
        printf("To Exit press E, else type anything and press enter to do another computation... \n> ");
        scanf("%s", &flag_status);
        
        if (flag_status == 'E') 
            return 0;

        else 
        {
            printf("Addition or Subtration of two integers (a (+ or -) b)\n");
            printf("> ");
        }
    }
}