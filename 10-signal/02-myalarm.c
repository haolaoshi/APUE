#include "00-apue.h"
#include <signal.h>
#include <pwd.h>


static void my_alarm(int signo)
{
    struct passwd *rootptr;

    printf("in signal handlern");
    if((rootptr = getpwnam("root")) == NULL)
        err_sys("getpwnam(root) eoorr");
    alarm(1);
}


int main()
{
    struct passwd *ptr;
//    signal(SIGALRM ,my_alarm);
    alarm(1);
    for(;;){
        if((ptr = getpwnam("unix")) == NULL)
            err_sys("getpwnam error");

        if(strcmp(ptr->pw_name,"unix") != 0)
            printf("NOT UNIX, return value corrupter,pw_name = %s\n",ptr->pw_name);
    } 
}
