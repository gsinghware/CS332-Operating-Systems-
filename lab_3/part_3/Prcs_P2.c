#include <stdio.h>												// Standard Input Output Functions
#include <fcntl.h>												// defines options flags
#include <unistd.h>												// Prototypes for many system calls
#include <string.h>												// Commenly used for string handling functions (strerror())
#include <errno.h>												// Declares errno and defines error constants

int main (int argc, char* argv[])							
{
	if (argc != 4) 												// 3 args required
	{			
        printf("Need 2 arguments for copy program\n");			// ./exec source, dest1, dest2 
        return 1;												// exit if false args provided
    }

	char *source = argv[1];										// source file
	char *destination1 = argv[2];								// destination file 1
	char *destination2 = argv[3];								// destination file 2
		
	int fd, d1, d2, n;
	fd = open(source, O_RDONLY);								// open the source file with RD only access
	
	if (fd >= 0)												// file opened successfully
	{
		int dummy_var = access(destination1, F_OK);				// check if destination file exists
		if (dummy_var == 0)										// if it does
			unlink(destination1);								// delete it because we don't want to overwrite it
		
		d1 = open(destination1, O_CREAT | O_RDWR, S_IRWXU);		// new file created with read and write access using flags
		
		dummy_var = access(destination2, F_OK);					// check if destination file exists
		if (dummy_var == 0)										// if it does
			unlink(destination2);								// delete it because we don't want to overwrite it
		
		d1 = open(destination1, O_CREAT | O_RDWR, S_IRWXU);		// new file created with read and write access using flags
		d2 = open(destination2, O_CREAT | O_RDWR, S_IRWXU);		// new file created with read and write access using flags		

		if (d1 >= 0 and d2 >= 0)								// if file opened successfully
		{
			char buff[100];										// create buffer of size 100	
			int x = 101;
			while((n = read(fd, buff, x)) > 0)					// read 100 chars at a time
			{
        		if (x == 101) 
        		{
        			for (int i = 0; i <= sizeof(buff); i++)		// read the 100 chars and look for
					{											// 1's and replace them with A's
						if (buff[i] == '1') 
						{
							buff[i] = 'A';
						}
	        		}
        			write(d1, buff, n);							// write the updated buffer to the dd file
        			x = 51;
        		}
        		else
        		{
        			for (int i = 0; i <= sizeof(buff); i++)		// read the 100 chars and look for
					{											// 1's and replace them with A's
						if (buff[i] == '2') 
						{
							buff[i] = 'B';
						}
	        		}
        			write(d2, buff, n);							// write the updated buffer to the dd file
        			x = 101;
        		}
        	}
    	}
        else
			perror("open");										// print error if file doesn't open

		close (fd);												// close the source file
		close (d1);												// close the dest file
		close (d2);												// close the dest file
	} 
	else 
		perror("open");											// print error if any

	return 0;
}
