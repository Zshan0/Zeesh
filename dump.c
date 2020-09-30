void pipe_redirect(char *input_str)
{
	/*	
		First we check if there is any 
		output file, else the output 
		file is stdout.
	*/
	int append = append_or_not(input_str);
	char *split_output_redirect[10];
	char delim_output[2] = ">";
	parser(input_str, delim_output, \
		split_output_redirect);
	int stdout_save = -1, stdin_save = -1;
	char space[4] = " \t\n";
	if(split_output_redirect[1] != NULL)
	{
		char *output_file_name[2];
		parser(split_output_redirect[1],\
		 space, output_file_name);
		int output_fd;
		if(append == 1)
		{
			if((output_fd = \
				open(output_file_name[0], \
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
				open(output_file_name[0], \
				O_WRONLY | O_APPEND)) < 0)
			{
				printf("%s does not exist:\n", \
					output_file_name[0]);
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
	/*
		Redirection of output has been managed,
		Now redirection of input.
	*/
	char delim_input[5] = "<";
	char *split_input_redirect[100];
	parser(split_output_redirect[0],\
	 delim_input, split_input_redirect);
	
	if(split_input_redirect[1] != NULL)
	{
		char *input_file_name[2];
		parser(split_input_redirect[1],\
		space, input_file_name);
		int input_fd;
		if((input_fd = \
			open(input_file_name[0], \
			O_RDONLY)) < 0)
		{
			printf("%s does not exist:\n", \
				input_file_name[0]);
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
	/*
		PIPING
	*/
	char *pipe_separated[100];
	char delim_pipe[2] = "|";
	parser(split_input_redirect[0],\
	 		delim_pipe, pipe_separated);
	/* 
		Pipe from the stdin to a pipe
		which will then be used for 
		further piping as the old pipe.
	*/
	int pos = 0;
	int fd[2];
	int old_pipe = 1;
	while(pipe_separated[pos] != NULL)
	{
		char *parsed_cmd[100];
		parser(pipe_separated[pos], \
				space, parsed_cmd);
		history(parsed_cmd);
		if(strcmp(parsed_cmd[0], "exit") == 0)
			inbuilt_no_output(parsed_cmd);
		else if(strcmp(parsed_cmd[0], "cd") == 0)
		{
			inbuilt_no_output(parsed_cmd);
			pos += 1;
			continue;
		}
		pipe(fd);
		pid_t pid;
		if((pid = fork()) < 0)
		{
			perror("pipe fork:");
			return;
		}
		output_exit = 1;
		if(pid == 0)
		{
			/* Child process will execute
			and write into the piped file.
			Close the reading file. */
			close(fd[0]);
			if(dup2(fd[1], old_pipe) < 0)
			{
				perror("dup2 pipes:");
				return ;
			}
			if(strcmp(parsed_cmd[0],\
					 "pinfo") == 0)
				inbuilt_fork(parsed_cmd);
			else if(strcmp(parsed_cmd[0],\
					 "else") == 0)
				inbuilt_fork(parsed_cmd);
			else if(strcmp(parsed_cmd[0],\
					 "echo") == 0)
				inbuilt_fork(parsed_cmd);
			else if(strcmp(parsed_cmd[0], \
					"history") == 0)
				inbuilt_fork(parsed_cmd);
			else if(strcmp(parsed_cmd[0], \
					"nightswatch") == 0)
				inbuilt_fork(parsed_cmd);
			else if(strcmp(parsed_cmd[0],\
					 "pwd") == 0)
				inbuilt_commands_no_fork(
				 	parsed_cmd);
			else
				ground(parsed_cmd);
			fflush(stdout);
			exit(0);
		}
		else 
		{
			int wstatus;
			while((waitpid(pid, &wstatus, 0)) > 0)
				break;
			close(fd[1]);
			old_pipe = fd[0];
			pos += 1;
		}
	}
	int read_value;
	while(old_pipe != 1)
	{
		char *output = (char *) \
						malloc(sizeof(char)\
						 * buffer_size);
		read_value = read(old_pipe, output, \
								buffer_size);
		if(read_value <= 0)
			break;
		printf("%s", output);
	}
	fflush(stdin);
	fflush(stdout);
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
	return;
}
