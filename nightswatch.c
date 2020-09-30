#include "nightswatch.h"

/*
	Implementation of watch command.
	has 2 options with time gap whose
	default value is 5.
	-interrupt
		Shows the number of interrupts
		made by the keyboard(i8042).
	-newborn
		Shows the latest process ran
		on the system.
	So far the only way to terminate is
	to use ctrl + c and kill the entire
	shell.
*/

int main(int arguments, char *parsed_input[])
{
	
	/*
		If the number of seconds has
		been passed then it reads it
		and changes the time from default
		of 5 to the new value.
	*/
	int pos = 1;
	int time = 2;
	if(strcmp(parsed_input[pos], "-n") == 0)
	{
		pos += 1;
		char *end; 
		time = strtol(parsed_input[pos], &end, 10);
		short range_error = errno == ERANGE;
		if(range_error == 1)
		{
			printf("out of range number\n");
			return 1;
		}
		pos += 1;
	}
	/*
		Based on the option. one of the
		2 functions are called.
	*/
	if(strcmp(parsed_input[pos], "interrupt") == 0)
	{
		nightswatch_interrupt(time);
	}
	else if(strcmp(parsed_input[pos], "newborn") == 0)
	{
		nightswatch_newborn(time);
	}
	else
	{
		printf("unknown option");
	}
	return 1;
}


void nightswatch_newborn(int time)
{
	while(1)
	{
		int file = open("/proc/loadavg", O_RDONLY);
		char *str = (char *) malloc(sizeof(char) * 1000);
		int read_value;
		if((read_value = read(file, str, 1000)) <= 0)
		{
			perror("read interrupts");
			exit(1);
		}
		str = realloc(str, read_value);
		char *line = strtok(str, "\n");
		//splitting it into the numbers
		char *num_str;
		char *last_num;
		num_str = strtok(line, " \t\n");
		while(num_str != NULL)
		{
			last_num = num_str;
			num_str = strtok(NULL, " \t\n");
		}
		printf("%s\n", last_num);
		fflush(stdout);
		sleep(time);
	}

}

void nightswatch_interrupt(int time)
{
	int fd = open("/proc/interrupts", \
				O_RDONLY);
	if(fd == -1)
	{
		perror("interrupt read");
		exit(1);
	}
	char *buffer = (char *)malloc(sizeof(char)\
									* 1000);
	if((read(fd, buffer, 1000)) <= 0)
	{
		perror("read interrupts");
		exit(1);
	}
	char *line_1 = strtok(buffer, "\n");
	/*
		printing the CPU numbers with 
		proper spacing.
	*/
	char *cpu = strtok(line_1, " \t\n");
	while(cpu != NULL)
	{
		printf("%10s", cpu);
		cpu = strtok(NULL, " \t\n");
	}
	printf("\n");
	/*
		Reading the file again and again
		inside the loop and then displaying 
		the 3rd line which represents the 
		keyboard interrupts.
	*/
	while(1)
	{
		int file = open("/proc/interrupts", \
						O_RDONLY);
		char *str = (char *) malloc(sizeof(char) * \
					1000);
		if((read(file, str, 1000)) <= 0)
		{
			perror("read interrupts");
			exit(1);
		}
		char *line = strtok(str, "\n");
		line = strtok(NULL, "\n");
		line = strtok(NULL, "\n");
		//splitting it into the numbers
		char *num_str = strtok(line, " \t\n");
		while(num_str != NULL)
		{
			/*
				In the given keyboard interrupt line
				it starts with the serial number of 
				the line and then followed by the 
				number of interrupts and then
				the interrupt name.
			*/
			num_str = strtok(NULL, " \t\n");
			if((num_str[0] <= '9') && \
				(num_str[0] >= '0'))
				printf("%10s", num_str);
			else
				break;
		}
		printf("\n");
		fflush(stdout);
		sleep(time);
	}

}