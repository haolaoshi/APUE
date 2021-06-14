#include <signal.h>
#include <errno.h>
#include "00-apue.h"

#define SIGBAD(signo) ((signo) <=0 || (signo) >= NSIG)

int sigaddset(sigset_t *set,int signo)
{
    if(SIGBAD(signo)) {
        errno = EINVAL;
        return -1;
    }
    *set |= 1 << (signo - 1);
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

void pr_mask(const char* str)
{
    sigset_t sigset;
    int errno_save;
    errno_save = errno;

    if(sigprocmask(0,NULL,&sigset)<0){
        err_ret("sigprocmask error");
    }else{
        printf("%s",str);
        if(sigismemeber(&sigset,SIGINT))
            printf("SIGINT"); 
        if(sigismember(&sigset,SIGQUIT))
            printf("SIGQUIT");
        if(sigismemeber(&isgset,SIGUSR1)
            printf("ISGUSR1");
        if(sigismemeber(&&sigset,SIGALRM));

    }


}
