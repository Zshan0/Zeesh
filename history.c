#include "header.h"
extern size_t buffer_size;
extern char *shell_path;
/*
	Writes the newest command into 
	the history.txt where the top 
	most command is the most recent
	one.
*/


void history(char *input_parsed[])
{
	//getting the path for the file where the history is written
	char *path = (char *) malloc(sizeof(char) * (strlen(shell_path) + 15));
	strcpy(path, shell_path);
	strcat(path, "/");
	strcat(path, "history.txt");
    chmod(path, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	int fd;
	if((fd = open(path, O_CREAT | O_RDWR)) == -1)
	{
		perror("history open:");
		return ;
	}
	//reading the contents of the history file into a string
	char *history_mem = (char *) malloc(sizeof(char) * buffer_size);
	int read_val;
	if((read_val = read(fd, history_mem, buffer_size)) == -1)
	{
		close(fd);
		perror("history read:");
		return ;
	}
	history_mem = realloc(history_mem, read_val + 1);
	history_mem[read_val] = '\0';
	//copying the new input into a new string
	char *write_history = (char *) malloc(sizeof(char) * (strlen(history_mem) + buffer_size + 1));
	int pos = 0;
	while(input_parsed[pos] != NULL)
	{
		strcat(write_history, input_parsed[pos]);
		strcat(write_history, " ");
		pos += 1;
	}
	strcat(write_history, "\n");
	//copying the old commands into the string with new line separation.
	int counter = 1;
	char delim[2] = "\n";
	char *piece = strtok(history_mem, delim);
	while(piece != NULL)
	{
		strcat(write_history, piece);
		strcat(write_history, "\n");
		piece = strtok(NULL, delim);
		counter += 1;
		if(counter == 20)
			break;
	}	
	//writing the newly formed string back to the file from the start
	lseek(fd, 0, SEEK_SET);
	if((write(fd, write_history, (strlen(write_history) + 1))) < 0)
	{
		close(fd);
		perror("history write:");
		return ;
	}
	close(fd);
	return;
}