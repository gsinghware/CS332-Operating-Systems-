#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	int x, y;													// x: number of chapters, y: number of homework(s)
	printf("> Number of chapters? -> ");
	while(scanf("%d", &x) == 1)
	{
    	if (x > 1) 
    		break;
    	else
    		printf("> x must be greater than 1, try again... -> ");
    }
    
	printf("> Number of homework(s)? -> "); 					// prompt number of hw's per chapter
	while(scanf("%d", &y) == 1) 
	{
    	if (y >= 1) 
    		break;
    	else
    		printf("> y must be greater than or equal to 1, try again... -> ");
    }

    int std_num = 10;											// num of students
    int quiz_grades[std_num][x*y];								// data array
    pid_t director = fork();									// director pid
    int status;													// director pid status
    pid_t manager;												// manager pid
    int status1; 												// manager status1
    pid_t worker;												// worker pid
    int status2; 												// worker status2
    double average = 0.0;										// average for columns

    FILE *source; 												// create file pointer for source file
	source = fopen("quiz_grades", "r"); 						// open source file file
	int grade;

	// load data into a 2d array
	for(int i = 0; i < std_num; i++)							// 10 rows
	{
		for (int j = 0; j < x * y; j++)							// x * y cols
		{
			fscanf(source, "%d", &grade);						// get the grade
			quiz_grades[i][j] = grade;							// put it in the array
		}
	}

	fclose(source);												// close the file

    if (director == -1)                                         // if fork() returns -1, an error.
    {
        perror("The fork failed to create child 1.");
        exit(EXIT_FAILURE);
    }
    else if (director == 0)                                     // child 1 successfully forked
    {
    	// manager processes
    	int manager_count = 0;
    	int worker_count = 0;
    	int cur_row = 0;
    	int cur_col = 0;
    	while (manager_count < x)								// until all chaps are done
    	{
    		manager = fork();									// manager fork
    		if (manager == -1)                                 	// if fork() returns -1, an error.
		    {
		        perror("The fork failed to create child 2.");
		        exit(EXIT_FAILURE);
		    }
		    else if (manager == 0)
		    {
		    	// worker processes
		    	while (worker_count < y) {
			    	worker = fork();
			    	if (worker == -1)                        	// if fork() returns -1, an error.
				    {
				        perror("The fork failed to create child 3.\n");
				        exit(EXIT_FAILURE);
				    }
				    else if (worker == 0)
				    {
				    	// printf("yes\n");
				    	// printf("%d\n", cur_row);
				    	// printf("%d\n", cur_col);
				    	printf("\t\t\tGrades for chapter %d and quiz %d is [", manager_count, cur_col);
				    	for (cur_row = 0; cur_row < 10; cur_row++)
				    	{
				    		printf("%d ", quiz_grades[cur_row][cur_col]);
				    		average += quiz_grades[cur_row][cur_col];
				    	}
				    	average = average/10.0;
				    	printf("]\n\t\t\tThe average for chapter %d and quiz %d is %f \n", manager_count, cur_col, average);
				    	_exit(EXIT_SUCCESS);
				    }
				    else
				    {
				    	printf("\t\t<<<<<< WORKER %d >>>>>>\n", worker_count);
				    	worker_count++;
				    	waitpid(worker, &status2, 0);
				    	cur_col++;
				    }
				}
				_exit(EXIT_SUCCESS);
		    }
		    else
		    {
		    	printf("\t<<<<<< MANAGER %d >>>>>>\n", manager_count);
		    	manager_count++;
		    	waitpid(manager, &status1, 0);
		    	cur_col += y;
		    }
    	}
    	_exit(EXIT_SUCCESS);
    }	
    else 
    {
    	printf("<<<<<< DIRECTOR >>>>>>\n");
    	// director processes
    	
		/* 
		// print data
		for(int i = 0; i < std_num; i++)
		{
			for (int j = 0; j < x * y; j++)
			{
				printf("%d ", quiz_grades[i][j]);
			}
			printf("\n");
		}
		*/

		waitpid(director, &status, 0);									// wait for the manager to finish

    }
    return 0;
}