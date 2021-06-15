#include "00-apue.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

volatile sig_atomic_t quitflag;

static void sig_int(int signo)
{
    if(signo == SIGINT)
        printf("\nintterupt\n");
    else if(signo == SIGQUIT)
        quitflag = 1;

}

int main()
{
    sigset_t newmask,oldmask,zeromask;
    if(signal(SIGINT,sig_int) == SIG_ERR)
        err_sys("error when install sigint");

    if(signal(SIGQUIT,sig_int) == SIG_ERR)
        err_sys("error when install SIGquit");

    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask,SIGQUIT);

    if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
        err_sys("SIGBLOCK ERROR");

    while(quitflag == 0)
        sigsuspend(&zeromask);

    quitflag = 0;
    if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
        err_sys("error when setmask");

    exit(0);

}
