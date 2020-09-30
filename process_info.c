#include "process_info.h"

extern size_t buffer_size;
extern int path_length;


char* process_mem(pid_t pid)
{
	size_t buffer_size = 1000;
	char *proc_stat = (char *) malloc(sizeof(char) * 50);
	sprintf(proc_stat, "/proc/%d/status", pid);
	int fd = open(proc_stat, O_RDONLY);
	if(fd == -1)
	{
		perror("proc file:");
		return '\0';
	}
	char *str = (char *) malloc(sizeof(char) * buffer_size);
	char delim[10] = " \t\n";
	char *mem;
	int read_value;
	/*
		We iterate over the file until
		"VmSize:" is found, then the
		next value read is size. 
	*/
	do{
		read_value = read(fd, str, buffer_size);
		if(read_value == -1)
		{
			perror("read in process status");
			exit(1);
		}
		mem = strtok(str, delim);
		while(mem != NULL)
		{
			mem = strtok(NULL, delim);
			if(strcmp(mem, "VmSize:") == 0)
			{
				mem = strtok(NULL, delim);
				return mem;
			}	

		}
	}while(read_value > 0);
	close(fd);
	return '\0';
}

char* process_name(pid_t pid)
{
	size_t buffer_size = 100;
	char *proc_stat = (char *) \
						malloc(sizeof(char) * 50);
	sprintf(proc_stat, "/proc/%d/status", pid);
	int fd = open(proc_stat, O_RDONLY);
	if(fd == -1)
	{
		// perror("proc file:");
		return '\0';
	}
	char *str = (char *) malloc(sizeof(char) * \
									buffer_size);
	int read_value = read(fd, str, buffer_size);
	if(read_value == -1)
	{
		perror("read");
		return '\0';
	}
	char delim[10] = " \t\n";
	char *name = strtok(str, delim);
	name = strtok(NULL, delim);
	close(fd);
	return name;
}

/*
	Function which returns the process path
	based on the exe symlink present in /proc
	folder of the given pid
*/

char* process_path(pid_t pid)
{
	size_t buffer_size = 1000;
	char *proc_exe = (char *) malloc(sizeof(char) * 50);
	sprintf(proc_exe, "/proc/%d/exe", pid);
	char *path = (char *) malloc(sizeof(char) * buffer_size);
	/*
		readlink to read the path of the given pid
	*/
	if(readlink(proc_exe, path, buffer_size) == -1)
	{
		perror("ReadLink:");
		return '\0';
	}
	
	return path;
}

/*
	Process which return the status of
	the process. It is read from 
	/proc/<pid>/status
*/

char* process_status(pid_t pid)
{
	size_t buffer_size = 100;
	char *proc_stat = (char *) malloc(sizeof(char) * 50);
	sprintf(proc_stat, "/proc/%d/status", pid);
	/*
		Opening the status file for 
		the given pid, this contains 
		the Status of the process
	*/
	int fd = open(proc_stat, O_RDONLY);
	if(fd == -1)
	{
		perror("proc file:");
		return '\0';
	}
	char *str = (char *) malloc(sizeof(char) * buffer_size);
	char delim[10] = " \t\n";
	char *name;
	int read_value;
	/*
		Read the file until "State:"
		is found, after that, the next
		value read which is the status.
	*/
	do{
		read_value = read(fd, str, buffer_size);
		if(read_value == -1)
		{
			perror("read in process status");
			return '\0';
		}
		name = strtok(str, delim);
		while(name != NULL)
		{
			name = strtok(NULL, delim);
			if(strcmp(name, "State:") == 0)
			{
				name = strtok(NULL, delim);
				return name;
			}	

		}
	}while(read_value > 0);
	close(fd);
	return '\0';
}
