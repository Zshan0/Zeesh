#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <ctype.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <limits.h>
#include <stddef.h>

//colors for the prompt display
#define GREEN "\033[0;32m"
#define CYAN "\033[0;36m"
#define DEFAULT "\033[0m"
extern int errno;
void UI(int args, char *argv[]);
void prompt();
void parser(char *string, char *delim, char *array[]);
void user_exit(char *input_str);
void echo(char *parsed[]);
char* PWD();
void inbuilt_argument_setter(char *input_parsed[]);
int inbuilt_no_output(char *input_parsed[]);
void change_dir(char *parsed_input[]);
void list_dir_contents(char *path, int a_flag, int l_flag);
void history(char *input_parsed[]);
void ground(char *parsed[]);
int foreground(char *parsed[]);
int background(char *parsed[]);
void signal_handler(int signum);
void signal_setup();
void Command_execution(char *commands[], int *old_pipe_input, int *old_pipe_output);
void Individual_command_execution(char *parsed[], int *old_pipe_input, int *old_pipe_output);
void pipe_redirect(char *input_str);
int append_or_not(char *input_str);
void Pipe(char *command, int read_file, int write_file);
void Child_execution(char *parsed[], int *fd, int *old_pipe_input, int *old_pipe_output, int background);
void Parent_execution(char *parsed[], int *fd, int *old_pipe_input, int *old_pipe_output, pid_t pid, int background);
int env(char *args[]);