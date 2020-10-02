#include "header.h"


int env(char *args[])
{
	int arguments = 0;
	while(args[arguments] != NULL)
		arguments += 1;
	if(arguments == 1 || arguments > 3)
	{
		printf("Illegal number of arguments\n");
		return 0;
	}
	char *command; command = args[0];
	char *name; name = args[1];
	char *value; value = args[2];
	if(value == NULL)
	{
		value = "";
	}
	if(strcmp(command, "setenv") == 0)
	{
		if((setenv(name, value, 1)) == -1)
		{
			perror("setenv:");
			return 1;
		}
		printf("Environment variable %s set to \"%s\"\n", name, getenv(name));
	}
	else if(strcmp(command, "unsetenv") == 0)
	{
		if(name == NULL)
		{
			printf("No name specified\n");
			return 1;
		}
		if((unsetenv(name)) == -1)
		{
			perror("unsetenv:");
			return 1;
		}
	}
	else if(strcmp(command, "getenv") == 0)
	{
		if(name == NULL)
		{
			printf("No name specified\n");
			return 1;
		}
		char *value = getenv(name);
		if(value != NULL)
			printf("%s\n", value);
		else 
			printf("variable not found\n");
		return 1;
	}
	else
	{
		return 0;
	}
	return 0;
}