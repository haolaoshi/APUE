#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXLINE 1024

//static void err_doit(int,int,const char*,va_list);


static void err_doit(int errnoflag, int error,const char* fmt,va_list ap);

void err_quit(char *str)
{
    printf("%s\n",str);
    exit(-1);
}


void err_ret(const char *fmt,...)
{
    va_list ap;
    va_start(ap,fmt);
    err_doit(1,errno,fmt,ap);
    va_end(ap);

}


void err_sys(const char *s, ... )
{
    va_list ap;
    va_start(ap,s);
    err_doit(1,errno,s,ap);
    va_end(ap);

    exit(1);
}

static void err_doit(int errnoflag, int error,const char* fmt,va_list ap)
{
    char buf[MAXLINE];
    vsnprintf(buf,MAXLINE-1,fmt,ap);
    if(errnoflag)
        snprintf(buf+strlen(buf),MAXLINE-strlen(buf)-1, ": %s",strerror(error));
    strcat(buf,"\n");
    fflush(stdout);
    fputs(buf,stderr);
    fflush(NULL);
}
