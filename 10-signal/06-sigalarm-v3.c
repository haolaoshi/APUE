#include "00-apue.h"
#include <unistd.h>
#include <setjmp.h>
#include <signal.h>

static jmp_buf env_alrm;


static void sig_int(int signo)
{
    int i,j;
    volatile int k;
    printf("\nsig_int staring...%d\n",k);

    for(i = 0; i < 300000; i++)
        for(j =0; j < 4000; j++)
            k += i * j;
    printf("sig_int finished\n");

}

unsigned int sleep2(unsigned int seconds)
{
    if(signal(SIGALRM,sig_int) == SIG_ERR)
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
    if(signal(SIGINT,sig_int) == SIG_ERR)
        err_sys("error install signal(SIGINT)");
    unslept = sleep2(5);
    printf("sleep1 returned : %u\n",unslept);
    exit(0);
}
