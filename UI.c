#include "header.h"

/*
    Function which initializes 
    the values of paths and 
    names for the prompt.
*/

extern char *shell_path;
extern size_t buffer_size;
extern int output_file_no;
extern int input_file_no;
extern char *hostname, *systemname;
extern int hostname_size;
extern int systemname_size;
extern int path_length;


void UI(int args, char *argv[])
{
    if(args == 1)
    {
    	output_file_no = 1;
    	input_file_no = 0;
        hostname = (char *) malloc(sizeof(char) * hostname_size);
        if(getlogin_r(hostname, 100) == -1)
        {
            perror("Error:");
            exit(1);
        }
        systemname = (char *) malloc(sizeof(char) * systemname_size);
        if(gethostname(systemname, 100) == -1)
        {
            perror("gethostname:");
            exit(1);
        }
        shell_path = PWD();
    }
    else 
    {
        printf("Illegal number of arguments");
        exit(1);
    }
}