#include "header.h"
#include "process_info.h"
extern int number_of_jobs;
extern struct Process proc[100];



void jobs_updated()
{
	struct Process dup[100];
	int pos = 0;
	for(int i = 0; i < number_of_jobs; i += 1)
	{
		if(kill(proc[i].pid, 0) == -1)
		{
			continue;
		}
		dup[pos].pid = proc[i].pid;
		dup[pos].name = process_name(proc[i].pid);
		dup[pos].stat = proc[i].stat;
		pos += 1;
	}
	for(int i = 0; i < pos; i += 1)
	{
		proc[i].pid = dup[i].pid;
		proc[i].name = dup[i].name;
		proc[i].stat = dup[i].stat;
	}
	number_of_jobs = pos;
}

void status_update(pid_t pid, int status)
{
	for(int i = 0; i < number_of_jobs; i += 1)
	{
		if(proc[i].pid == pid)
		{
			proc[i].stat = status;
		}
	}
}

void display_jobs()
{
	jobs_updated();	
	for(int i = 0; i < number_of_jobs; i += 1)
	{
		printf("[%d] ", (i + 1));
		if(WIFEXITED(proc[i].stat))
			continue;
		else if(WIFSTOPPED(proc[i].stat))
			printf("Stopped %s [%d]\n", proc[i].name, proc[i].pid);
		else
			printf("Running %s [%d]\n", proc[i].name, proc[i].pid);
	}
	fflush(stdout);
}

void Signal_processes(char *parsed[])
{
	for(int i = 0; i <= 2; i += 1)
	{
		if(parsed[i] == NULL)
		{
			printf("Invalid number of arguments\nkjob job_num signal\n");
			return;
		}
	}
	/* 
		index [1] followed by signum [2]
	*/
	char *end;	
	int index = strtol(parsed[1], &end, 10);
	int signum = strtol(parsed[2], &end, 10);
	if(index > number_of_jobs || index <= 0)
	{
		printf("Not a valid job number\n");
		return ;
	}
	pid_t req_pid = proc[index - 1].pid;
	if(kill(req_pid, signum) == -1)
	{
		perror("kill:");
		return;
	}
	jobs_updated();
}

void job_ground(char *parsed[])
{
	if(parsed[1] == NULL)
	{
		printf("Invalid number of arguments\nfd job_num\n");
		return ;
	}
	char *end;
	int index = strtol(parsed[1], &end, 10);
	if(index > number_of_jobs || index <= 0)
	{
		printf("Not a valid job number\n");
		return ;
	}
	pid_t req_pid = proc[index - 1].pid;
	if(strcmp(parsed[0], "fg") == 0)
	{
		int wstatus;
		signal(SIGTTOU, SIG_IGN);
		int terminal_pid = tcgetpgrp(0);
		tcsetpgrp(0, req_pid);
		tcsetpgrp(1, req_pid);
		while(waitpid(req_pid, &wstatus, WUNTRACED) > 0)
			break;
		tcsetpgrp(1, terminal_pid);
		tcsetpgrp(0, terminal_pid);
	}
	else if(strcmp(parsed[0], "bg") == 0) 
	{
		if(kill(req_pid, SIGCONT) == -1)
		{
			perror("kill:");
			return;
		}
		
	}
	jobs_updated();
}


/* 
	Kill all the child 
	processes.
*/ 
void job_overkill()
{
	for(int i = 0; i < number_of_jobs; i += 1)
	{
		pid_t pid = proc[i].pid;
		if(kill(pid, SIGKILL) == -1)
		{
			perror("kill:");
			return;
		}
	}
	jobs_updated();
}
