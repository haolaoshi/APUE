#include "00-apue.h"
#include <pthread.h>


struct foo{
    int a,b,c,d;
};

void printfoo(const char *s,const struct foo *f)
{
    printf("%s",s);
    printf("   structure at 0x%lx\n",(unsigned long)f);
    printf("   foo.a = %d\n",f->a);
    printf("   foo.b = %d\n",f->b);
    printf("   foo.c = %d\n",f->c);
    printf("   foo.d = %d\n",f->d);
}

void *thr_fn1(void *arg)
{
    struct foo f = {1,2,3,4};
    printfoo("thread 1:\n",&f);
    pthread_exit((void*)&f);
}

void *thr_fn2(void *arg)
{
    printf("thread 2 : ID is %lu\n",(unsigned long)pthread_self());
    pthread_exit((void*)0);
}

int main()
{
    int err;
    pthread_t tid1,tid2;
    struct foo  *f;

    err = pthread_create(&tid1,NULL,thr_fn1,NULL);
    if(err != 0)
        err_exit(err,"cannot create thread 1");

    err = pthread_join(tid1,(void*)&f);
    if(err != 0)
        err_exit(err,"canno join thread 1");

    sleep(1);

    printf("present starting second thread.");
    err = pthread_create(&tid2,NULL,thr_fn2,NULL);
    if(err != 0)
        err_exit(err,"cannot create thread 2");
    sleep(1);
    printfoo("parent: \n",f);
    exit(0);
}
