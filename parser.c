#include "header.h"
extern int buffer_size;


void parser(char *string, char delim[], char *array[])
{
	int pos = 0;
	char *left;
	array[0] = (char *) malloc(sizeof(char) * buffer_size);
	array[0] = strtok_r(string, delim, &left);
	pos += 1;
	while(1)
	{
		array[pos] = (char *) malloc(sizeof(char) * buffer_size);
		array[pos] = strtok_r(NULL, delim, &left);
		if(array[pos] == NULL)
			break;
		pos += 1;
	}
	fflush(stdout);
	return;
}