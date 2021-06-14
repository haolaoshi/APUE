#include "00-apue.h"
#include <unistd.h>

//signal handler 
static void sig_alrm(int signo)
{
    printf("Received a signal %d\n",signo);
}


unsigned int sleep1(unsigned int seconds)
{
    if(signal(SIGALRM,sig_alrm) == SIG_ERR)
        return (seconds);
    alarm(seconds);
    pause();
    return (alarm(0));
}

int main()
{
    unsigned int unslept;
    /*Install a signal handler*/
    if(signal(SIGINT,sig_alrm) == SIG_ERR)
        err_sys("error install signal(SIGINT)");
    unslept = sleep1(5);
    printf("sleep1 returned : %u\n",unslept);
    exit(0);
}
