#include "header.h"

extern int errno;
char *shell_path, *prev_dir;
size_t buffer_size = 1000;
char *hostname, *systemname;
int hostname_size = 100;
int systemname_size = 100;
int path_length = 100;
int output_file_no = 1;
int input_file_no = 1;
int output_exit = 0;
int number_of_jobs = 0;
struct Process proc[100];
int foreground_pid = 0;
int foreground_wait = 1;
int parent_pid;


int main(int args, char *argv[])
{
	hostname = NULL; systemname = NULL;
    /*signal handling setup*/
	signal_setup();
    /*setting up the paths and names for the shell in UI function (refer UI.c)*/
    UI(args, argv);
    /*Shell loop*/
    while(1)
    {
        /*displaying the prompt of the shell in the 
        	start of every loop*/
        prompt();
        char *input_str = (char *) \
        				malloc(buffer_size * sizeof(char));
        int read_value = read(0, input_str, buffer_size);
        if(read_value == 0)
        {
        	printf("\n");
        	exit(0);
        }
        input_str = realloc(input_str, \
        			(sizeof(char) * (read_value + 1)));
        input_str[read_value] = '\0';
        char delim[10] = ";\n";
        char *parsed[100];
        parser(input_str, delim, parsed);
        int pos = 0;
        while(1)
        {
        	if(parsed[pos] == NULL)
        		break;
        	pipe_redirect(parsed[pos]);
        	pos += 1;
        }   
        jobs_updated();
        free(input_str); input_str = NULL;
    }
    return 0;
}

