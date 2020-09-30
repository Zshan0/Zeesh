#include "ls_header.h"
/*
	Function which prints the owner of
	the file.
*/

void file_owner_name(char *full_path)
{
	struct stat buf;
	if(stat(full_path, &buf) == -1)
		return;
	struct passwd *psd;
	psd = getpwuid(buf.st_uid);
	if(psd == NULL)
	{
		perror("file owner:");
		exit(1);
	}
	printf("%s ", psd->pw_name);
}