#include "header.h"

extern char *hostname, *systemname, *shell_path;


void user_exit(char *input_str)
{
	free(hostname); hostname = NULL;
	free(systemname); systemname = NULL;
	free(shell_path); shell_path = NULL;
	free(input_str); input_str = NULL;
	exit(1);
}