#include "00-apue.h"
#include <sys/wait.h>

#define MAX_LINE 1024
static void sig_int(int);

int main()
{
    char command_line[MAX_LINE];
    pid_t  pid;
    int status;

    if(signal(SIGINT,sig_int) == SIG_ERR)
        err_sys("signal error");

    printf("%% ");
    while(fgets(command_line,MAX_LINE,stdin) != NULL){
        if(command_line[MAX_LINE - 1] == '\n')
            command_line[MAX_LINE - 1] = 0;
        if(( pid = fork()) < 0)
            err_sys("fork error");
        else if(pid == 0){
            execlp(command_line,command_line,(char*)0);
            err_ret("Couldn't execute: %s",command_line);
            exit(127);
        }
        printf("FATHER(%ld),CHILD(%ld)\n",(long)getpid(),(long)pid);
        if((pid == waitpid(pid,&status,0)) < 0)
            err_sys("wait pid error");
        printf("%% ");
    }
    exit(0);
}

void sig_int(int signo)
{
    printf("interrupt [%d]\n%% ",signo);

}
