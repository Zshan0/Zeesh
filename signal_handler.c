#include "header.h"
#include "process_info.h"

extern int path_length;
extern int output_exit;
extern int number_of_jobs;
extern struct Process proc[100];

/*
	Functions to handle the signals 
	for interrupt, terminate and 
	the child signal. 
	displays the exit code and for
	child signal it displays the name
	of the process which terminated.
*/

void signal_setup()
{
	struct sigaction setup;
	sigemptyset(&setup.sa_mask);
	/* Blocking other signals */
	sigaddset (&setup.sa_mask, SIGINT);
	sigaddset (&setup.sa_mask, SIGQUIT);
	sigaddset (&setup.sa_mask, SIGCHLD);
	setup.sa_handler = signal_handler;

	setup.sa_flags = SA_RESTART;
	if(sigaction(SIGCHLD, &setup, NULL) < 0)
		perror("sigaction:");
	if(sigaction(SIGINT, &setup, NULL) < 0)
		perror("sigaction:");
	if(sigaction(SIGTERM, &setup, NULL) < 0)
		perror("sigaction:");
}




void signal_handler(int signum)
{
	if(signum == SIGINT)
	{
		status_update(getpid(), -1);
		char output[1000];
		sprintf(output, \
			"\nProcess %d interrupted\n",\
			 getpid());
		write(2, output, strlen(output));
		exit(1);
	}
	else if(signum == SIGTERM)
	{
		status_update(getpid(), -1);
		char output[1000];
		sprintf(output, \
			"\nProcess %d terminated\n", \
			getpid());
		write(2, output, strlen(output));
		exit(1);
	}
	else if(signum == SIGCHLD)
	{
		char output[1000];
		int status;
		jobs_updated();
		int pid;
		while((pid = \
			waitpid(-1, &status, WNOHANG)) > 0)
		{
			int i;
			for(i = 0; i < number_of_jobs; i += 1)
			{
				if(proc[i].pid == pid)
				{
					break;
				}
			}
			if (WIFEXITED(status))
			{
				status_update(pid, -1);
				sprintf(output, \
				"\n%s with pid %d exited,status=%d\n", \
				proc[i].name, pid, \
				WEXITSTATUS(status));
			} 
			else if (WIFSIGNALED(status))
			{
				status_update(pid, -1);
				sprintf(output, \
				"\n%s with pid %d killed by signal %d\n", \
				proc[i].name, pid, \
				WTERMSIG(status));
			}
			else if (WIFSTOPPED(status)) 
			{
				status_update(pid, 0);
				sprintf(output, \
				"\n%s with pid %d stopped by signal %d\n", \
				proc[i].name, pid, \
				WSTOPSIG(status));
			}
			else if (WIFCONTINUED(status))
			{
				status_update(pid, 1);
				sprintf(output, \
				"\n%s with pid %d continued\n", \
				proc[i].name, pid);
			}
			if(output_exit == 0)
				write(2, output, strlen(output));
		}
	}
}