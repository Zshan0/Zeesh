#include "header.h"
extern char *shell_path;
extern int buffer_size;
extern int path_length;
extern int parent_pid;

void inbuilt_argument_setter(char *input_parsed[])
{
	char *executable = (char *) malloc(sizeof(char) * buffer_size);
	strcpy(executable, shell_path);
	if(strcmp(input_parsed[0], "echo") == 0)
	{
		strcat(executable, "/exec/echo");
		input_parsed[0] = executable;
	}
	else if(strcmp(input_parsed[0], "pinfo") == 0)
	{	
		strcat(executable, "/exec/pinfo");
		input_parsed[0] = executable;
		input_parsed[1] = (char *) malloc(sizeof(char) * 10);
		sprintf(input_parsed[1], "%d", parent_pid);
		input_parsed[2] = NULL;
	}
	else if(strcmp(input_parsed[0], "history") == 0)
	{
		strcat(executable, "/exec/print_history");
		input_parsed[0] = executable;
		char *input = shell_path;
		if(input_parsed[1] == NULL)
		{
			input_parsed[1] = "10";
		}
		input_parsed[2] = input;
		input_parsed[3] = NULL;
	}
	else if(strcmp(input_parsed[0], "nightswatch") == 0)
	{
		strcat(executable, "/exec/nightswatch");
		input_parsed[0] = executable;
	}
	else if(strcmp(input_parsed[0], "pwd") == 0)
	{
		strcat(executable, "/exec/echo");
		input_parsed[0] = executable;
		// printf("Here here");
		char *input = PWD();
		// char *input = "pwd";
		input_parsed[1] = input;
		input_parsed[2] = NULL;
	}
	else if(strcmp(input_parsed[0], "ls") == 0)
	{
		char *pwd = PWD();
		int pos = 1;
		int dirs = 0;
		while(input_parsed[pos] != NULL)
		{
			if(input_parsed[pos][0] != '-')
			{
				char *args = (char *) malloc(sizeof(char) * path_length);
				strcpy(args, pwd);
				strcat(args, "/");
				strcat(args, input_parsed[pos]);
				strcat(args, "/");
				input_parsed[pos] = args;
				dirs += 1;
			}
			pos += 1;
		}
		if(dirs == 0)
		{
			char *args = PWD();
			if(args[strlen(args) - 1] != '/')
				strcat(args, "/");
			input_parsed[pos] = args;
			pos += 1;
		}
		input_parsed[pos] = NULL;
		free(pwd); pwd = NULL;
		strcat(executable, "/exec/ls");
		input_parsed[0] = executable;
	}
	return ;
}

int inbuilt_no_output(char *input_parsed[])
{
	if(strcmp(input_parsed[0], "exit") == 0)
	{
		user_exit(input_parsed[0]);
		return 1;
	}	
	else if(strcmp(input_parsed[0], "cd") == 0)
	{
		change_dir(input_parsed);
		return 1;
	}
	else if( (strcmp(input_parsed[0], "setenv") == 0)||\
			(strcmp(input_parsed[0], "unsetenv") == 0)||\
			(strcmp(input_parsed[0], "getenv") == 0))
	{
		env(input_parsed);
		return 1; 
	}
	return 0;
}
int inbuilt_output(char *input_parsed[])
{
	if(strcmp(input_parsed[0], "jobs") == 0)
	{
		display_jobs();
		return 1;
	}
	else if(strcmp(input_parsed[0], "kjob") == 0)
	{
		Signal_processes(input_parsed);
		return 1;
	}
	else if(strcmp(input_parsed[0], "fg") == 0)
	{
		job_ground(input_parsed);
		return 1;
	}
	else if(strcmp(input_parsed[0], "bg") == 0)
	{
		job_ground(input_parsed);
		return 1;
	}
	else if(strcmp(input_parsed[0], "overkill") == 0)
	{
		job_overkill();
		return 1;
	}
	else
		return 0;
}