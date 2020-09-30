#include "ls_header.h"
int path_length = 100;

int main(int args, char *parsed[])
{
	char *dirs[100];
    int a_flag = 0;
    int l_flag = 0;
    int pos = 1;
    int dir_count = 0;
    while(parsed[pos] != NULL)
    {
    	if(parsed[pos][0] == '-')
    	{
    		int len = strlen(parsed[pos]);
    		for(int i = 1; i < len; i += 1)
    		{
    			if(parsed[pos][i] == 'a')
    				a_flag = 1;
    			else if(parsed[pos][i] == 'l')
    				l_flag = 1;
    		}
    	}
    	else
    	{
    		dirs[dir_count] = parsed[pos];
			dir_count += 1;
    	}
    	pos += 1;
    }
    for(int i = 0; i < dir_count; i += 1)
    {
    	// printf("%s\n", dirs[i]);
        list_dir_contents(dirs[i], a_flag, l_flag);
        // free(dirs[i]); dirs[i] = NULL;
    }
    return 0;
}

void list_dir_contents(char *path, int a_flag, int l_flag)
{
	struct dirent *dir_pointer;
    DIR *cur_dir = opendir(path);
    fflush(stdout);
    /*
        If the directory does not exist then it is returned with an
        error message. Else it will print the contents.
    */
    if(cur_dir == NULL)
    {
        printf("\n %s Directory doesn't exist\n", path);
        return;
    }
    else
    {
        if(path[strlen(path) - 1] != '/')
            strcat(path, "/");
        dir_pointer = readdir(cur_dir);
        /*
            Based on the flags passed, the output is obtained
        */ 
        while(dir_pointer != NULL)
        {
            if(l_flag == 1)
                display_file_info(path, dir_pointer->d_name, a_flag);
            else if(a_flag == 1)
                printf("%s\n", dir_pointer->d_name);
            else if(dir_pointer->d_name[0] != '.')
                printf("%s\n", dir_pointer->d_name);
            dir_pointer = readdir(cur_dir);
        }     
    }
	fflush(stdout);
}