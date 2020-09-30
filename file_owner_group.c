#include "ls_header.h"
/*
	file to display the group of 
	the owner of the file 
*/


void file_owner_group(char *full_path)
{
	struct stat buf;
	if(stat(full_path, &buf) == -1)
		return;
	struct group *grp = getgrgid(buf.st_gid);
	if(grp == NULL)
	{
		perror("owner group:");
		exit(1);
	}
	printf("%s ", grp->gr_name);
}