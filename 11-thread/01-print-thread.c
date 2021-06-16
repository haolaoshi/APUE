#include "00-apue.h"
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

pthread_t ntid;

void printids(const char *s)
{
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();

    printf("%s pid %lu tid %lu (0x%lx)\n",s,(unsigned long)pid,
        (unsigned long)tid,(unsigned long)tid);

}

void *thr_fn(void *arg)
{
    printids("new thread: ");
    return ((void *)0);
}

int main(void)
{
    int err;
/*
    int nt pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start_routine) (void *), void *arg);
*/


    err = pthread_create(&ntid,NULL,thr_fn,NULL);
    if(err != 0)
        err_exit(err,"can't create thread");

    printids("main thread:");
    sleep(1);
    exit(0);
}
