#include "header.h"

int main(int args, char *array[])
{
	int pos = 1;
	while(1)
	{
		if(array[pos] == NULL)
			break;
		printf("%s ", array[pos]);
		pos += 1;
	}
	printf("\n");
	return 0;
}
