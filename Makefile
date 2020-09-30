all: shell ls pinfo print_history nightswatch

shell: header.h main.c process_info.h process_info.c prompt.c UI.c parser.c user_exit.c directories.c inbuilt.c history.c ground.c foreground.c background.c signal_handler.c pipe_redirect.c env.c
	gcc -o z header.h main.c process_info.h process_info.c prompt.c UI.c parser.c user_exit.c directories.c inbuilt.c history.c ground.c foreground.c background.c signal_handler.c pipe_redirect.c env.c -Wall
ls: ls_header.h ls.c permission_display.c display_file_info.c file_owner_group.c file_owner_name.c file_size.c last_modified_time.c
	gcc -o ./exec/ls ls_header.h ls.c permission_display.c display_file_info.c file_owner_group.c file_owner_name.c file_size.c last_modified_time.c -Wall
pinfo: pinfo.c process_info.c process_info.h
	gcc -o ./exec/pinfo process_info.h pinfo.c process_info.c -Wall
print_history: print_history.h print_history.c parser.c
	gcc -o ./exec/print_history print_history.h print_history.c parser.c -Wall
nightswatch: nightswatch.h nightswatch.c
	gcc -o ./exec/nightswatch nightswatch.h nightswatch.c -Wall