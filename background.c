#include "header.h"

/*
	Function to run commands in the
	background. It will fork the process
	Change the PID of the child and make it
	orphan. Which will then execute the 
	command using execvp. After it 
	terminates, child handler will handle
	the clean up by exiting it.
*/

int background(char *parsed[])
{

	int pos = 1;
	while(parsed[pos] != NULL)
	{
		if(strcmp(parsed[pos], "&") == 0)
		{
			parsed[pos] = NULL;
			break;
		}
		pos += 1;
	}

	pid_t id = fork();
	if(id == -1)
	{
		perror("fork:");
		exit(1);
	}
	/*
		Since it runs in the background,
		There is no need to wait in the 
		parent process, just return.
	*/
	if(id > 0)
		return 1;
	else if(id == 0)
	{
		/*
			change the pid of the program
			and then run execvp.
		*/
		if(setpgid(0, 0) == -1)
		{
			perror("setpgid:");
			exit(1);
		}
	    if(execvp(parsed[0], parsed) != -1)
		{
			return 1;
		}
	}
	return 1;
}