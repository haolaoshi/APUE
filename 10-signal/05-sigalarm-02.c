#include "00-apue.h"
#include <unistd.h>
#include <setjmp.h>

//signal handler 
static jmp_buf env_alrm;


static void sig_alrm(int signo)
{
    longjmp(env_alrm,1);
}


unsigned int sleep1(unsigned int seconds)
{
    if(signal(SIGALRM,sig_alrm) == SIG_ERR)
        return (seconds);
    alarm(seconds);
    pause();
    return (alarm(0));
}


unsigned int sleep2(unsigned int seconds)
{
    if(signal(SIGALRM,sig_alrm) == SIG_ERR)
        return (seconds);
    if(setjmp(env_alrm) == 0){
       alarm(seconds);
       pause();
    }
    return (alarm(0));
}


int main()
{
    unsigned int unslept;
    /*Install a signal handler*/
    if(signal(SIGINT,sig_alrm) == SIG_ERR)
        err_sys("error install signal(SIGINT)");
    unslept = sleep2(5);
    printf("sleep1 returned : %u\n",unslept);
    exit(0);
}
