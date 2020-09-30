#include "header.h"
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


extern int errno;

int directory_check(char *path);
long long int file_size(char *file_path);
void list_dir_contents(char *path, int a_flag, int l_flag);
void display_file_info(char *file_path, char *file_name, int a_flag);
void permission_display(char *file_path);
long long int file_size(char *file_path);
void file_owner_name(char *full_path);
void file_owner_group(char *full_path);
char* last_modified_time(char *file_path);
char* PWD();