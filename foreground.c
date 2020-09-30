#include "header.h"

/*
	To run some comamnds which are 
	present in /usr/bin. This will 
	fork the process into 2. The parent
	process will wait for the child process
	which will run the given command using
	execvp.
*/

int foreground(char *parsed[])
{
	/*
		Forking the current process
		and the if the return value is
		0 then it is the child process.
		else it is the parent process.
	*/
	pid_t id = fork();
	if(id == -1)
	{
		perror("fork:");
		exit(1);
	}
	else if(id == 0)
	{
		
	    if(execvp(parsed[0], parsed) != -1)
		{
			printf("Command not found\n");
			return 0;
		}
	}
	else
	{
		/*
			Wait for the child process to end.
			and then return back to the 
			shell loop.
		*/
		int wstatus;
		while((waitpid(id, &wstatus, 0)) > 0)
			break;
	}
	return 1;
}