#include "00-apue.h"


int main()
{
    if(chdir("/tmp") < 0)
        err_sys("chdir failed.");
    printf("chdir to /tmp succeded\n");
    exit(0);
}
