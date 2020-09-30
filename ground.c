#include "header.h"


void ground(char *parsed[])
{
	int back = 0;
	int pos = 0;
	/* checking if it is background or 
	foreground process */
	while(parsed[pos] != NULL)
	{
		if(strcmp(parsed[pos], "&") == 0)
		{
			back = 1; break;
		}
		pos += 1;
	}
	if(back == 0)
		foreground(parsed);
	else
		background(parsed);
	return;
}