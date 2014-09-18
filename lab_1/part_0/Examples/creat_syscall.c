/* This program explains use of creat( ) system call*/
 
#include <stdio.h> 
#include <sys/types.h> 	/* defines types */ 
#include <sys/stat.h> 	/* defines S_IREAD & S_IWRITE */ 
#include <fcntl.h>
#include <unistd.h>		// for close
 
int main( ) 
{ 
	int fd; 
	fd = creat("datafile.dat", S_IREAD | S_IWRITE); 

	if (fd == -1) 
		printf("Error in opening datafile.dat\n"); 
	
	else 
	{ 
		printf("datafile.dat opened for read/write access\n"); 
		printf("datafile.dat is currently empty\n"); 
	}

	close(fd);
	return 0;
}