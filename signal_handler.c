#include "header.h"
#include "process_info.h"

extern int path_length;
extern int output_exit;

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

	// setup.sa_mask = blocked;
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
		char output[100];
		sprintf(output, \
			"\nProcess %d interrupted\n",\
			 getpid());
		write(2, output, strlen(output));
		exit(1);
	}
	else if(signum == SIGTERM)
	{
		char output[100];
		sprintf(output, \
			"\nProcess %d terminated\n", \
			getpid());
		write(2, output, strlen(output));
		exit(1);
	}
	else if(signum == SIGCHLD)
	{
		char output[100];
		int process_pid[1000] = {0};
		char process_names[1000][path_length];
		int pos = 0;
	    struct dirent *dir_pointer;
		DIR *cur_dir = opendir("/proc/");
		dir_pointer = readdir(cur_dir);
		while(dir_pointer != NULL)
		{
			char *pid_str = dir_pointer->d_name;
			if( (pid_str[0] <= '9') && \
				(pid_str[0] >= '0'))
			{
				char *end; 
				int pid = \
				strtol(pid_str, &end, 10);
				process_pid[pos] = pid;
				strcpy(process_names[pos],
							process_name(pid));
				pos += 1;
			}
			dir_pointer = readdir(cur_dir);
		}
		int status;
		int pid;
		while((pid = \
			waitpid(-1, &status, WNOHANG)) > 0)
		{
			int i;
			for(i = 0; i < pos; i += 1)
			{
				if(process_pid[i] == pid)
					break;
			}
			if (WIFEXITED(status)) 
				sprintf(output, \
				"\n%s with pid %d exited,\
				 status=%d\n", \
				process_names[i], pid, \
				WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				sprintf(output, \
				"\n%s with pid %d \
				killed by signal %d\n", \
				process_names[i], pid, \
				WTERMSIG(status));
			else if (WIFSTOPPED(status)) 
				sprintf(output, \
				"\n%s with pid %d \
				stopped by signal %d\n", \
				process_names[i], pid, \
				WSTOPSIG(status));
			else if (WIFCONTINUED(status))
				sprintf(output, \
				"\n%s with pid %d continued\n", \
				process_names[i], pid);
			if(output_exit == 0)
				write(2, output, strlen(output));
		}
	}
}