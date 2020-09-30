#include "ls_header.h"

/*
    Displaying the permission of the file
    using stat structure.
*/

void permission_display(char *file_path)
{
    struct stat file;
    int file_return = stat(file_path, &file);
    if(file_return == -1)
        return;
    char *permissions = (char *) malloc(sizeof(char) * 12);
    if(directory_check(file_path) == 0)
        strcpy(permissions, "-");
    else
        strcpy(permissions, "d");
    int perm_flags[10] = {S_IRUSR, S_IWUSR, S_IXUSR, \
                            S_IRGRP, S_IWGRP, S_IXGRP, \
                            S_IROTH, S_IWOTH, S_IXOTH}; 
    char options[3][2] = {"r", "w", "x"};
    /*
        Permissions by ANDING it with the st_mode
    */
    for(int i = 0; i < 9; i += 1)
    {
        if((perm_flags[i] & file.st_mode) > 0)
            strcat(permissions, options[i % 3]);
        else
            strcat(permissions, "-");
    }
    printf("%s ", permissions);
    free(permissions); permissions = NULL;
}
