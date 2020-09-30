#include "print_history.h"
size_t buffer_size = 1000;

/*
	Function which reads the local history 
	file present in the shell directory.
	In the file, the history is written in
	newest top format. This function reads the 
	mentioned number of commands and then
	prints those many in the reverse order
	with the help of a stack.
*/

int main(int arguments, char *parsed_input[])
{
	/* If no number has been passed then the default argument is 10 */
	int num;
	char *end; 
	num = strtol(parsed_input[1], &end, 10);
	short range_error = errno == ERANGE;
	/*
		If the entered number is out of 20
		it is returned with the error message.
	*/ 
	if(range_error == 1 || num > 20)
	{
		printf("out of range\n");
		return 1;
	}
	char *shell_path = parsed_input[2];


	char *path = (char *) malloc(sizeof(char) * \
							(strlen(shell_path) + 15));
	strcpy(path, shell_path);
	strcat(path, "/");
	strcat(path, "history.txt");
	/*
		All permissions for the history.txt
	*/
    chmod(path, S_IRUSR | S_IWUSR | S_IXUSR | \
    			S_IRGRP | S_IWGRP | S_IXGRP | \
    			S_IROTH | S_IWOTH | S_IXOTH);
	int fd;
	if((fd = open(path, O_CREAT | O_RDWR)) == -1)
	{
		perror("history open:");
		exit(1);
	}
	char *history_mem = (char *) malloc(sizeof(char) * \
						buffer_size);
	int read_val;
	if((read_val = read(fd, history_mem, buffer_size)) == -1)
	{
		close(fd);
		perror("history read:");
		exit(1);
	}
	/*
		loading the whole history file into a string
		for printing it
	*/
	history_mem = realloc(history_mem, read_val + 1);
	history_mem[read_val] = '\0';
	char *commands[25];
	char delim[5] = "\n";
	parser(history_mem, delim, commands);
	int p = 0;
	while(commands[p] != NULL)
	{
		p += 1;
	}
	p -= 1;
	if(num < p)
	{
		p = num - 1;
	}
	while(p >= 0 && commands[p] != NULL)
	{
		printf("%s\n", commands[p]);
		p -= 1;
	}
	free(history_mem); history_mem = NULL;
	close(fd);
	return 1;
}