//
#include <dirent.h>
#include "00-apue.h"
#define  EVERGREEN "/var/spool/mail"
int main()
{
    char *ptr;
    size_t size;

    if(chdir(EVERGREEN) < 0)
        err_sys(EVERGREEN);
    ptr = malloc(PATH_MAX + 1);
    //ptr = path_alloc(&size);
    if(getcwd(ptr,size) == NULL)
        err_sys("getcwd failed.");
    printf("cwd = %s\n",ptr);
    exit(0);
}
