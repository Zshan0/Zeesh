#include "header.h"
#include "process_info.h"
extern int number_of_jobs;
extern struct Process proc[100];



void jobs_updated()
{
	for(int i = 0; i < number_of_jobs; i += 1)
	{
		if(proc[i].stat < 0)
			continue;
		if(process_name(proc[i].pid) != NULL)
		{
			proc[i].name = process_name(proc[i].pid);
		}
	}
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
		if(proc[i].stat == -1)
			continue;
		printf("[%d] ", (i + 1));
		if(proc[i].stat == 0)
			printf("Stopped %s [%d]\n", proc[i].name, proc[i].pid);
		else
			printf("Running %s [%d]\n", proc[i].name, proc[i].pid);
	}
	fflush(stdout);
}