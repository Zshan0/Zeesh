# Zeesh - Shell in C

## Introduction

Shell with some basic functionalities written in C with the help of system header files.

## How to use

- Clone the directory
- run `make` inside the directory.
- `./z` to run the shell.
- `exit` to exit out of the shell.

# Features

## Built-in features

### Indentation insensitive

Regardless of where you write the command by adding spaces or tabs, it will behave in the same way.

### ; separated commands

You can run more than 1 shell command in  a single line by separating them with a `;`

### ls

- Lists the contents of the given directory.
- Add `-l` to display the details of each file.
- Add `-a` to display the hidden contents.
- The directories and flags can be mentioned in any order after ls

### cd

- change the current working directory to the relative or the absolute path passed as argument.
- `~` to go back to the shell executable directory.
- `..` to go to the previous directory.
- `-` will change your directory to the previous directory you were in.

### pwd

- To see the present working directory `pwd`.

### pinfo

- Displays the process information.
    - Process ID
    - Process Status
    - Virtual memory
    - executable path.
- If the PID is not mentioned it will show the information about the shell process.

### History

- Displays the last used commands with most recent ones appearing at the bottom of the list.
- stores uptill 20 history commands.

### Nightswatch [incomplete]

- gives the output of 2 particular commands continuously till interrupted.
- `nightswatch -n [time] {interrupt/newborn}`
- **interrupt:**
    - Shows the number of keyboard interrupts handled by each CPU
- **newborn:**
    - Shows the last run process on the system.

### File redirection

- `<` is used for input redirection. `cat < input` File contents of input are redirected to stdin and cat is executed.
- `>`  is used for output redirection. `ls > output` the output of ls is redirected to output file.
- Both of them can be combined together in a single command.

 

### Piping

- `|` Can be used to redirect one commands output to another file. `ls | wc` Will redirect the output of ls to wc.
- More than 2 commands can be chained together for piping.

### Environment variables

- `setenv` can be used to overwrite the value of a environment variable to the given value.
- `unsetenv` can be used to remove the variable from the environment.
- `getenv` can be used to print the value of the given environment variable.

### Jobs

- Jobs are processes spawned by the shell, `jobs` will list the processes spawned by the shell along with their status and the pid.
- `kjob job_number signal_number` Will send the signal to the given job.
- `overkill` Will kill all background processes at once.
- `exit` Will exit out of the shell.

### Signal handling

- `ctrl+z` will kill send the current foreground process to the background and will stop the process.
- `ctrl+c` will interrupt the currently running foreground process, if no foreground process is present, it will do nothing.

### fg/bg [Incomplete]

- `fg` can be used to bring a background process to the foreground process. The shell will only continue to execute after the process has terminated.
- `bg` can be used to make a stopped background process run again.