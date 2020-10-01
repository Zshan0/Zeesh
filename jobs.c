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
			continue;
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

void Signal_processes(int signum, pid_t pid)
{

}