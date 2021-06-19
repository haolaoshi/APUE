#include "00-apue.h"

#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>


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

    //attach file desc 0, 1 and 2 to /dev/null
    fd0 = open("/dev/null",O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    openlog(cmd, LOG_CONS,LOG_DAEMON);
    if(fd0 != 0|| fd1 != 1 || fd2 != 2){
        syslog(LOG_ERR, "unexpected file desc %d %d %d ",fd0,fd1,fd2);
        exit(1);
    }
}

//void daemonize(const char *cmd)

int main()
{
    const char *cmd = "date"; 
    daemonize(cmd);

    sleep(20);
    exit(0);
}
