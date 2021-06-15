#include "00-apue.h"
#include <setjmp.h>
#include <time.h>


static void sig_usr1(int);
static void sig_alrm(int);
static  sigjmp_buf  jmpbuf;
static volatile sig_atomic_t canjmp;

void pr_mask(const char* str);


int main()
{
    if(signal(SIGUSR1,sig_usr1) == SIG_ERR)
        err_sys("error signal SIGUSR1 ");

    if(signal(SIGALRM,sig_alrm) == SIG_ERR)
        err_sys("error signal SIGALRM ");

    pr_mask("starting main:");
    if(sigsetjmp(jmpbuf,1)) {
        pr_mask("ending main:");
        exit(0);
    }

    canjmp = 1;
    for(;;)
        pause();

    exit(0);
}

static void sig_usr1(int signo)
{
    time_t starttime;
    if(canjmp == 0)
        return ;

    pr_mask("starting sig_usr1:");
    alarm(3);

    starttime = time(NULL);
    for(;;)
        if(time(NULL) > starttime + 5)
            break;
    pr_mask("finishing sig_usr1:");
    canjmp = 0;

    siglongjmp(jmpbuf,1);
}

static void sig_alrm(int signo)
{

    pr_mask("in sig_alrm:");

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


