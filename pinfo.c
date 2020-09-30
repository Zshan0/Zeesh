#include "process_info.h"

/*
	Function to display:
		-PID 
		-Status
		-Memory (Virtual)
		-Path
	of the process
*/

size_t buffer_size = 1000;
int path_length = 100;

int main(int args, char *input_parsed[])
{
	pid_t pid;
	/*
		If there is no PID then the PID
		is of the current progress.
	*/
	if(input_parsed[1] == NULL)
	{
		pid = getpid();
	}
	else
	{
		char *end; 
		pid = strtol(input_parsed[1], &end, 10);
		short range_error = errno == ERANGE;
		if(range_error == 1)
		{
			printf("out of range ID\n");
			return 0;
		}
	}
	/*
		Separate functions for memory,
		status and executable.
	*/
	printf("PID -- %d\n", pid);
	printf("Process Status -- %s\n", \
					process_status(pid));
	printf("Memory -- %s\n", process_mem(pid));
	printf("Executable path -- %s\n", \
			process_path(pid));
	return 0;
}


