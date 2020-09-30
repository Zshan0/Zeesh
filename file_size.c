#include "ls_header.h"
/*
    returns the size of the program 
    by reading till the end of the file
    and returning the value of return.
*/ 
extern int path_length;

int directory_check(char *path)
{
    struct stat stats;
    if(stat(path,  &stats) != 0)
        return 0;
    return S_ISDIR(stats.st_mode);
}

char* PWD()
{
    char *cur_path = (char *) malloc(sizeof(char) * path_length);
    if (getcwd(cur_path, path_length) == NULL) 
        perror("error in pwd");
    return cur_path;
}


long long int file_size(char *file_path)
{
	int dir = directory_check(file_path);
	if(dir != 0)
		return 4096;
    int file = open(file_path, O_RDONLY);
    if(file == -1)
    {
    	perror("file_size:");
    	exit(1);
    } 
    long long int size = lseek(file, 0, SEEK_END);
    if(size == -1)
    {
    	perror("lseek:");
    	exit(1);
    }
    return size;
}