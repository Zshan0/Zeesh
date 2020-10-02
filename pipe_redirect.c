#include "header.h"
#include "process_info.h"

extern int buffer_size;
extern int output_exit;
extern int process_pid[1000];
extern int number_of_jobs;
extern struct Process proc[100];


int append_or_not(char *input_str)
{
	int len = strlen(input_str);
	int append = 0;
	for(int i = 0; i < len; i += 1)
	{
		if(input_str[i] == '>')
			append += 1;
	} 
	return append;
}

void pipe_redirect(char *input_str)
{
	int append = append_or_not(input_str);
	char space[4] = " \t\n";
	char *parsed[100];
	parser(input_str, space, parsed);
	history(parsed);
	int output_file_pos = -1;
	int input_file_pos = -1;
	char *commands[100];
	int command_counter = 0;
	int stdout_save = -1, stdin_save = -1;
	int redirected = 0;
	for(int i = 0; i < 100; i += 1)
	{
		if(parsed[i] == NULL)
			break;
		if(strcmp(parsed[i], "<") == 0)
		{
			i += 1;
			input_file_pos = i;
		}
		else if( (strcmp(parsed[i], ">") == 0)\
			 || (strcmp(parsed[i], ">>") == 0) )
		{
			i += 1;
			output_file_pos = i;
			redirected = 1;
		}
		else if(redirected == 0)
		{
			commands[command_counter]\
						 = parsed[i];
			command_counter += 1;
		}
	}	
	commands[command_counter] = NULL;
	int output_fd;
	if(output_file_pos != -1)
	{
		if(append == 1)
		{
			if((output_fd = \
				open(parsed[output_file_pos], \
				O_WRONLY |\
				O_TRUNC |\
				O_CREAT, 0644)) \
				 < 0)
			{
				perror("output file opening:");
				return ;
			}
		}
		else
		{
			if((output_fd = \
				open(parsed[output_file_pos], \
				O_WRONLY | O_APPEND)) < 0)
			{
				printf("%s does not exist:\n", \
					parsed[output_file_pos]);
				return ;
			}
		}
		stdout_save = dup(STDOUT_FILENO);
		if(dup2(output_fd, 1) < 0)
		{
			perror("dup2 output:");
			return ;
		}	
		close(output_fd);
	}
	else
	{
		output_fd = 1;
	}
	int input_fd;
	if(input_file_pos != -1)
	{
		if((input_fd = \
			open(parsed[input_file_pos], \
			O_RDONLY)) < 0)
		{
			printf("%s does not exist:\n", \
				parsed[input_file_pos]);
			return ;
		}
		stdin_save = dup(STDIN_FILENO);
		if(dup2(input_fd, 0) < 0)
		{
			perror("dup2 output:");
			return ;
		}
		close(input_fd);	
	}
	else
	{
		input_fd = 0;
	}
	int old_pipe_input = 0;
	int old_pipe_output = -1;
	Command_execution(commands,\
				 &old_pipe_input,\
				  &old_pipe_output);
	if((old_pipe_output != -1) && (dup2(1, old_pipe_output) < 0))
	{
		perror("dup2 error:");
		return;
	}
	fflush(stdin);
	if((stdout_save != -1) && \
		(dup2(stdout_save, 1) < 0))
	{
		perror("dup2 output:");
		return ;
	}
	if((stdin_save != -1) && \
		(dup2(stdin_save, 0) < 0))
	{
		perror("dup2 output:");
		return ;
	}
	if(old_pipe_input != 0)
	{
		close(old_pipe_input);
	}
}

void Command_execution(char *commands[],\
					 int *old_pipe_input,\
					  int *old_pipe_output)
{
	char *command[100];
	int pos_commands = 0;
	while(commands[pos_commands] != NULL)
	{
		for(int i = 0; i < 100; i += 1)
		{
			if(commands[pos_commands] == NULL)
			{
				pos_commands += 1;
				command[i] = NULL;
				*old_pipe_output = 1;
				break;
			}
			else if(strcmp(commands[pos_commands], "|")\
			  == 0) 
			{
				pos_commands += 1;
				command[i] = NULL;
				break;
			}
			command[i] = commands[pos_commands];
			pos_commands += 1;
		}
		if(inbuilt_no_output(command) == 1)
		{
			*old_pipe_output = 1;
		}
		else if(inbuilt_output(command) == 1)
		{
			*old_pipe_output = 1;
		}
		else	
		{
			Individual_command_execution(command, \
										old_pipe_input, \
										old_pipe_output);
		}
	}
	return;
}

void Individual_command_execution(char *parsed[], \
									int *old_pipe_input, \
									int *old_pipe_output)
{
	int background = 0;
	int pos = 0;
	while(parsed[pos] != NULL)
	{
		if(strcmp(parsed[pos], "&") == 0)
		{
			parsed[pos] = NULL;
			background = 1; break;
		}
		if(strcmp(parsed[pos], "nightswatch") == 0)
		{
			background = 1;
		}
		pos += 1;
	}

	int fd[2];
	pipe(fd);
	pid_t pid;

	if((pid = fork()) < 0)
	{
		perror("pipe fork:");
		return ;
	}
	if(pid == 0)
	{
		/*
			Child process. Close the 
			read file.
		*/
		Child_execution(parsed, fd, old_pipe_input, \
						old_pipe_output, background);
	}
	else 
	{
		/*
			Parent process, 
			close the write file.
		*/
		Parent_execution(parsed, fd, old_pipe_input, \
						old_pipe_output, pid, background);
		*old_pipe_output = fd[1];
	}
}

/*
	function to execute the child process.
	fd[0] will be the fd(file descriptor) for the 
		read end of pipe.
	fd[1] will be the fd for the write end of pipe.
	int dup2(int oldfd, int newfd);
*/
void Child_execution(char *parsed[], \
				int *fd, int *old_pipe_input, \
			int *old_pipe_output, int background)
{
	/* 
		Changing the output
		to fd[1], and the
		input to old_pipe
	*/
	close(fd[0]);
	/* 
		Default Execution of signal
	*/
	signal(SIGTSTP, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	/* 
		Reading from the old
		file.
	*/
	if(dup2(*old_pipe_input, 0) < 0)
	{
		perror("dup2 pipes:");
		return ;
	}
	/* Writing into the piped
		file.*/
	if((*old_pipe_output != 1) &&\
		 (dup2(fd[1], 1) < 0))
	{
		perror("dup2 pipes:");
		return ;
	}
	inbuilt_argument_setter(parsed);
	if(background == 1)
	{
		if(setpgid(0, 0) == -1)
		{
			perror("setpgid:");
			exit(1);
		}
	}
    if(execvp(parsed[0], parsed) != -1)
	{
		return ;
	}
	close(*old_pipe_input);
	close(fd[1]);
	exit(0);
}

void Parent_execution(char *parsed[], int *fd,\
					 int *old_pipe_input, \
					int *old_pipe_output, pid_t pid,\
					 int background)
{
	/*
		Closing the write file. 
	*/
	*old_pipe_input = fd[0];
	close(fd[1]);
	proc[number_of_jobs].pid = pid;
	if(background == 0)
	{
		proc[number_of_jobs++].stat = 127;
		int wstatus;
		while(waitpid(pid, &wstatus, WUNTRACED) > 0)
			break;
		jobs_updated();
	}
	else 
	{
		proc[number_of_jobs++].stat = 1;
		return ;
	}
}
