#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>

int main (void)
{	
	pid_t pid1 = fork();									// fork for child 1 

	int status1;
	if (pid1 == -1) 										// if fork() returns -1, an error.
	{
		perror("The fork failed to create child 1.");
		exit(EXIT_FAILURE);
	}

	else if (pid1 == 0)										// child 1 successfully forked
	{		
		printf("I am child one, my pid is: %d.\n", getpid());
		/*
			The first argument to execl is the filename of the command; 
			The second argument is conventionally the program name.
			If the command takes arguments, they are strung out after this; 
			The end of the list is marked by a NULL argument.
		*/
		char *argv[4];
		argv[0] = "Prcs_P1";									
		argv[1] = "dest1.txt";									
		argv[2] = "dest2.txt";									
		argv[3] = NULL;										// Indicates the end of arguments

		execv(argv[0], argv);								// argv[0] is command name
    	printf ("EXECL Failed, date not found. \n");						
	}
	else {

		int status2;
		pid_t pid2 = fork();								// fork for child 2
 
		if (pid2 == -1)										// if fork() returns -1, an error.
		{
			perror("The fork failed to create child 2.");
			exit(EXIT_FAILURE);
		}
		else if (pid2 == 0)									// child 2 successfully forked
		{
			printf("I am child two, my pid is: %d.\n", getpid());
			char *argv[4];
			argv[0] = "Prcs_P2";
			argv[1] = "source.txt";									
			argv[2] = "dest1.txt";									
			argv[3] = "dest2.txt";									
			argv[4] = NULL;										// Indicates the end of arguments

			execv(argv[0], argv);								// argv[0] is command name
	    	printf ("EXECL Failed, date not found. \n");	
		}
		else												// parent of child 1 and child 2
		{
			printf("I am the parent process, my pid is: %d\n", getpid());
		
			waitpid(pid1, &status1, 0);							// wait for process 1 to be completed
			
			if (WIFSIGNALED(status1) == 0)						// WIFSIGNALED chks if child process if finished
			{
				printf("The child one process terminated normally.\n");
			}

			waitpid(pid2, &status2, 0);						// wait for process 1 to be completed
			if (WIFSIGNALED(status2) == 0)					// WIFSIGNALED chks if child process if finished
			{
				printf("The child two process terminated normally.\n");
			}

			printf("The Parent is:  %d.\n", getpid());		// The parent process is the last one.
		}
   	}

   	printf("The parent process also terminated.: %d\n", getpid());

	return 0;
}