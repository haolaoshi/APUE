#define _NSIG   64
#define _NSIG_BPW   32
#define _NSIG_WORDS (_NSIG / _NSIG_BPW)
/*
typedef unsigned long old_sigset_t;
typedef struct {
unsigned long sig[_NSIG_WORDS];
}sigset_t;
*/
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include "00-apue.h"

#define SIGBAD(signo) ((signo) <=0 || (signo) >= NSIG)
static void sig_quit(int);

/*
int sigaddset(sigset_t *set,int signo)
{
    if(SIGBAD(signo)) {
        errno = EINVAL;
        return -1;
    }
    
    *set = *set->sig | 1 << (signo - 1);
    return 0;
}

int sigdelset(sigset_t *set,int signo)
{
    if(SIGBAD(signo)){

    }
    *set &= ~(1 << (signo - 1));
    return 0;
}

int sigismember(const sigset_t *set,int signo)
{
    if(SIGBAD(signo)){
        errno = EINVAL;
        return -1;
    }
    return (*set & ( 1 << (signo - 1))) != 0;
}
*/
void pr_mask(const char* str)
{
    sigset_t sigset;
    int errno_save;
    errno_save = errno;

    if(sigprocmask(0,NULL,&sigset)<0){
        err_ret("sigprocmask error");
    }else{
        printf("%s",str);
        if(sigismember(&sigset,SIGINT))
            printf("SIGINT"); 
        if(sigismember(&sigset,SIGQUIT))
            printf("SIGQUIT");
        if(sigismember(&sigset,SIGUSR1))
            printf("ISGUSR1");
        if(sigismember(&sigset,SIGALRM));
            printf("SIGALRM");
        printf("\n");
    }

    errno = errno_save;
}

int main()
{
    sigset_t newmask,oldmask,pendmask;

    if(signal(SIGQUIT,sig_quit) == SIG_ERR)
        err_sys("cannot catch SIGQUIT");



    sigemptyset(&newmask);
    sigaddset(&newmask,SIGQUIT);
    if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0)
        err_sys("ISG_BLOCK ERROR");

    sleep(5);
    if(sigpending(&pendmask) < 0)
        err_sys("SIG_PENDING error");

    if(sigismember(&pendmask,SIGQUIT))
        printf("\nSIGQUIT pending\n");

    if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0)
        err_sys("SIG_SETMASK error");

    printf("SIGQUIT unblocked\n");

    sleep(5);
    exit(0);

}

static void sig_quit(int signo)
{
    printf("caught SIGQUIT\n");
    if(signal(SIGQUIT,SIG_DFL) == SIG_ERR)
        err_sys("cannot reset SIGQUIT");

}
