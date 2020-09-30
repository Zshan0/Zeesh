#include "ls_header.h"

/*
	shows the last modified time
	by reading it from the stat
	structure.
*/

char* last_modified_time(char *file_path)
{
	struct stat buf;
	if(lstat(file_path, &buf) == -1)
	{
		perror("time:");
		exit(1);
	}
	char *time = ctime(&buf.st_mtime);
	time[strlen(time) - 1] = '\0';
	return time;
}