#include "header.h"

/*
	prints the prompt with system 
	name and the user name.
*/
extern char *hostname, *systemname;
extern size_t buffer_size;
extern int output_file_no;


void prompt()
{
    char *rel = PWD();
    char *output = (char *) malloc(sizeof(char) * buffer_size);
    sprintf(output, "%s%s%s@%s%s:%s>%s", GREEN, hostname, CYAN, GREEN, systemname, Relative_path(rel), DEFAULT);
    write(output_file_no, output, strlen(output));
    free(rel); rel = NULL;
}