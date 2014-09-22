#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
	char *filepath = argv[1];

	int return_val;

	// check file existance
	return_val = access (filepath, F_OK);

	if (return_val == 0)									// if F_OK is 0, file exists
		printf("%s does exist\n", filepath);

	else 
	{
		if (errno == ENOENT) 								// errno - ENOENT - Error NO ENTry
			printf("%s does not exist\n", filepath);
		else if (errno == EACCES)							// EACCESS - permisssion denied
			printf("%s is not accessible\n", filepath);
		return 0;
	}

	// check read access
	return_val = access(filepath, R_OK); 					// access takes two args (filepath R_OK readable)
	
	if (return_val == 0)									// if R_OK is 0, file is readable
		printf("%s is readable \n", filepath);
	
	else
		printf("%s is not readable \n", filepath);			// file is not readable

	// check write access
	return_val = access(filepath, W_OK);					
	
	if (return_val == 0)									// if W_OK is 0, file is writeable
		printf("%s is Writeable \n", filepath);
	
	else if (errno == EACCES)								// if access is denied
		printf("%s is not Writeable (access denied) \n", filepath);	
	
	else if (errno == EROFS)								// if file is read only
		printf("%s is read-only \n", filepath);

	return 0;
}



