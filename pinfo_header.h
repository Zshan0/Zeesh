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

char* process_mem(pid_t pid);
char* process_name(pid_t pid);
char* process_path(pid_t pid);
char* process_status(pid_t pid);