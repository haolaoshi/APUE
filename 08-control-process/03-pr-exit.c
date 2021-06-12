#include "00-apue.h"
#include <sys/wait.h>


void pr_exit(int status)
{
    if(WIFEXITED(status))
        printf("normal termination,exit status = %d\n",WEXITSTATUS(status));
    else if(WIFSIGNALED(status))
        printf("abbnormal terminations ,signal number = %d%s\n",WTERMSIG(status),
#ifdef  WCOREDNUMP
        WCOREDUMP(status) ? " (core file generated)" :  "");
#else
        " ");
#endif
    else if(WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n",WSTOPSIG(status));

}

int main()
{
    pid_t pid;
    int status;

    if((pid = fork()) < 0)
        err_sys("fork error");
    else if(pid == 0)
        exit(7);

    if(wait(&status) != pid)
        err_sys("wait error");
    pr_exit(status);

    
    if((pid = fork()) < 0)
        err_sys("error_fork");

    else if(pid == 0);
        abort();

    if(wait(&status) != pid)
        err_sys("wait error");
    pr_exit(status);

    int a = 2;
    int b = 4;

    if((pid = fork()) < 0)
        err_sys("fork error");
    else if(pid == 0)
        status /= b/2 - 2;

    if(wait(&status) != pid)
        err_sys("wait error");
    pr_exit(status);

    exit(0);

}
