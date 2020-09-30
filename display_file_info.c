#include "ls_header.h"

/*
	For a given file path and the file name, this will 
	display the information based on the flags passed.
*/

void display_file_info(char *file_path, char *file_name, int a_flag)
{
	/*
		If the file is the current directory and
		the 'a' flag is absent, it returns.
	*/	
	if(file_name[0] == '.' && a_flag == 0)
		return;
	/*
		Getting the full path of the file 
	*/
	char *full_path = (char *) malloc(sizeof(char) * (strlen(file_path) + strlen(file_name) + 2));
	strcpy(full_path, file_path);
	strcat(full_path, file_name);
	/*
		Separate functions for each part of the 
		ls output.
	*/ 
	permission_display(full_path);
	file_owner_name(full_path);
	file_owner_group(full_path);
	printf("%10Ld ", file_size(full_path));
	printf("%s ", last_modified_time(full_path));
	printf("%s\n", file_name);
	free(full_path); full_path = NULL;
	return;
}