#include "00-apue.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/*

sigset_t newmask,oldmask;
sigemptyset(&newmask);

sigaddset(&newmask,SIGINT);

if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
    err_sys("SIG_BLOCK error");

if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
    err_sys("SIG_SETMask EER");

pause();

*/

static void sig_int(int);

int main()
{
    sigset_t newmask,oldmask,waitmask;
    pr_mask("progarm start:");

    if(signal(SIGINT,sig_int) == SIG_ERR)
        err_sys("ERROR when sigint ");

    sigemptyset(&waitmask);
    sigaddset(&waitmask,SIGUSR1);
    sigemptyset(&newmask);
    sigaddset(&newmask,SIGINT);
/*block sigint and save current signal mask*/
    if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
        err_sys("SIG_BLOCK error");

/*CRITICAL reagion*/
//allow all signals except usr1
    pr_mask("in critical region:");
    if(sigsuspend(&waitmask) != -1)
        err_sys("sispend error");

    pr_mask("after return from sigsuspend");
/*reset signal mask */
    if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
        err_sys("ERROR when setmask ");
//continue
    pr_mask("program exit:");

    exit(0);

}

static void sig_int(int signo)
{
    pr_mask("\nin sig_int:\n");

}
