#include "00-apue.h"
#include <pthread.h>
#include <syslog.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <sys/stat.h>
#include <signal.h>

#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

//extern int lockfile(int);
int lockfile(int fd)
{

    return 0;
}

int already_running(void)
{
    int fd;
    char buf[16];
    fd = open(LOCKFILE ,O_RDWR | O_CREAT,LOCKMODE);
    if(fd < 0){
        syslog(LOG_ERR,"cannot open %s : %s",LOCKFILE,strerror(errno));
        exit(1);
    }
    if(lockfile(fd) < 0){
        if(errno == EACCES || errno == EAGAIN){
            close(fd);
            return (1);
        }  
        syslog(LOG_ERR,"cannot lock %s : %s",LOCKFILE,strerror(errno));
        exit(1);
    }
    ftruncate(fd,0);
    sprintf(buf, "%ld",(long)getpid());
    write(fd,buf,strlen(buf) + 1);
    return (0);
}



void daemonize(const char *cmd)
{
    int i,fd0,fd1,fd2;
    pid_t pid;
    struct rlimit rl;
    struct sigaction sa;


//clear file creation mask;
    umask(0);
//get max number of file desc.
    if(getrlimit(RLIMIT_NOFILE,&rl) < 0)
        err_quit("can't get file limit ");
//become session leader 
    if((pid = fork()) < 0)
        err_quit("can't fork");
    else if(pid != 0)//parent!!
        exit(0);
    setsid();

   //ensure future opens won't allocate controlling tty.
   sa.sa_handler = SIG_IGN;

   sigemptyset(&sa.sa_mask);
   sa.sa_flags = 0;

   if(sigaction(SIGHUP,&sa,NULL) < 0)
       err_sys("error cannot ignore SIGUP %s\n",cmd);
    if((pid = fork()) < 0)
        err_sys("%s : cannot fork\n",cmd);
    else if(pid != 0) //parent 
        exit(0);


//change current dir to root 
    if(chdir("/") < 0)
        err_quit("change dir to / failed");

    //close all open file desc.
    if(rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for(i =0; i < rl.rlim_max; i++)
        close(i);
}


sigset_t mask;

extern int already_running(void);


void reread(void )
{

   printf("reading."); 
}


void *thr_fn(void *arg)
{
    int err,signo;
    for(;;){
        err = sigwait(&mask,&signo);
        if(err != 0){
            syslog(LOG_ERR,"sigwait failed");
            exit(1);
        }

        switch(signo){
        case SIGHUP:    
            syslog(LOG_INFO,"re-reading configuration file");
            reread();
            break;
        case SIGTERM:
            syslog(LOG_INFO,"got SIGTERM ; exiting;");
            exit(0);
        default:
            syslog(LOG_INFO,"unexpected signal %\n",signo);
        }
    }

    return (0);
}

int main(int argc, char* argv[])
{
    int err;
    pthread_t tid;
    char *cmd;
    struct sigaction sa;

    if((cmd = strrchr(argv[0],'/')) == NULL)
        cmd = argv[0];
    else
        cmd++;


    daemonize(cmd);
    if(already_running()){
        syslog(LOG_ERR,"daemon already running");
        exit(1);
    }

    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if(sigaction(SIGHUP,&sa,NULL) < 0)
        err_quit("%s: can't restore SIGHUP default");
    sigfillset(&mask);
    if((err = pthread_sigmask(SIG_BLOCK,&mask,NULL)) != 0)
        err_exit(err, "SIG_BLOCK_ERROR");

    err = pthread_create(&tid,NULL,thr_fn,0);
    if(err != 0)
        err_exit(err,"cannot' carete threawd");

  //  print("...proceed with thre rest of the daemon\n");
    sleep(20);

    exit(0);
}
