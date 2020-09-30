#include "header.h"

extern int path_length;
extern char *shell_path;

char* PWD()
{
    char *cur_path = (char *) malloc(sizeof(char) * path_length);
    if (getcwd(cur_path, path_length) == NULL) 
    	perror("error in pwd");
    return cur_path;
}

void change_dir(char *parsed_input[])
{
	if(parsed_input[1] == NULL)
	{
		fprintf(stderr, "Directory not mentioned\n");
		return ;
	}
	if(strcmp(parsed_input[1], ".") == 0)
		return ;
	if(parsed_input[1][0] == '/')
		if(chdir(parsed_input[1]) != 0) perror("Change directory");
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
		if(chdir(change_to) != 0) perror("Change directory");
	}
	else if(chdir(parsed_input[1]) != 0) perror("Change directory");
	free(cur_path); cur_path= NULL;
	free(change_to); change_to = NULL;
}
