#include "header.h"

extern int path_length;
extern char *shell_path;
extern char *prev_dir;

char* PWD()
{
    char *cur_path = (char *) malloc(sizeof(char) * path_length);
    if (getcwd(cur_path, path_length) == NULL) 
    	perror("error in pwd");
    return cur_path;
}

char* Relative_path(char *abs_path)
{
	int shell_path_length = strlen(shell_path);
	int abs_path_length = strlen(abs_path);
	if(abs_path_length < shell_path_length)
		return abs_path;
	int matched = 0;
	while(abs_path[matched] == \
			shell_path[matched])
		matched += 1;
	if(matched <\
		 shell_path_length)
		return abs_path;
	char *new_path = (char *) \
	malloc(sizeof(char) *\
			 (abs_path_length - matched + 1));
	new_path[0] = '~';
	for(int i = matched; i <\
				abs_path_length; i += 1)
	{
		new_path[(i + 1) - matched] =\
					 abs_path[matched]; 
	}
	new_path[(abs_path_length) - matched + 1] = '\0';
	return new_path;
}

void change_dir(char *parsed_input[])
{
	if(parsed_input[1] == NULL)
	{
		fprintf(stderr, "Directory not mentioned\n");
		return ;
	}
	if(strcmp(parsed_input[1], "-") == 0)
	{
		char *temp = prev_dir;
		prev_dir = PWD();
		if(chdir(temp) != 0) perror("Change directory"); 
		return;
	}
	if(strcmp(parsed_input[1], ".") == 0)
		return ;
	if(parsed_input[1][0] == '/')
	{
		free(prev_dir);
		prev_dir = PWD();
		if(chdir(parsed_input[1]) != 0)
		{
			perror("Change directory");
		}
		return ;
	}
	char *cur_path = PWD();
	char *change_to = (char *) malloc(sizeof(char) * path_length);
	if(parsed_input[1][0] == '~')
	{
		strcpy(change_to, shell_path);
		int pos = strlen(change_to);
		int i;
        for (i = 1; parsed_input[1][i] != '\0'; i++)
            change_to[i + pos - 1] = parsed_input[1][i];
        change_to[i + pos - 1] = '\0';
        free(prev_dir); prev_dir = PWD();
		if(chdir(change_to) != 0)
			perror("Change directory");
		return;
	}
	char *temp = prev_dir;
	prev_dir = PWD();
	if(chdir(parsed_input[1]) != 0) 
	{
		perror("Change directory");
		prev_dir = temp;
		return ;
	}
	free(cur_path); cur_path= NULL;
	free(change_to); change_to = NULL;
}
