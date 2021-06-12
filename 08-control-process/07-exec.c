#include "00-apue.h"

#include <sys/wait.h>


char *env_init[] = {"USER=unknown","PATH=/tmp",NULL};

int main()
{
    pid_t pid;
/*    if((pid = fork()) < 0){
        err_sys("error fork");
    }else if(pid == 0) {
        if(execle("/home/unix/Videos/UNIX/05-standardio/a.out","myarg","Myarg2",(char *)0,env_init) < 0)
            err_sys("execle error");
    }


    if(waitpid(pid,NULL,0) < 0)
        err_sys("wait error");
*/
    if((pid = fork()) < 0){
        err_sys("fork error");
    }else if(pid == 0){
        if(execlp("date","UNIX","only 1 arg",(char *)0) < 0)
            err_sys("execlp error");
    }

    exit(0);
}
///home/unix/Videos/UNIX/05-standardio/a.out*
