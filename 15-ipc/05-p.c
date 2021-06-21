#include "00-apue.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>


static pid_t *childpid = NULL;

static int maxfd;


FILE*
popen(const char *cmdstring, const char *type)
{
    int i;
    int pdf[2];

    pid_t pid;
    FILE *fp;

    if((type[0] != 'r' && type[0] != 'w') || type[1] != 0){
        errno = EINVAL;
        return (NULL);
    }
    
    if(childpid == NULL){
        maxfd = open_max();
        if((childpid = calloc(maxfd,sizeof(pid_t))) == NULL)
            return (NULL);
    }

    if(pipe(pdf) < 0)
        err_sys("error pipe");

    if(pdf[0] >= maxfd || pdf[1] >= maxfd){
        close(pdf[0]);
        close(pdf[1]);
        errno = EMFILE;
        return (NULL);
    }

    if((pid = fork()) < 0)
        err_sys("error fork()");

    else if(pid > 0){
        if(*type == 'r'){

        }else{

        }
        for(i = 0; i < maxfd; i++)
            if(childpid[i] > 0)
                close(i);
        execl("/bin/sh","sh","-c",cmdstring,(char*)0);
        _exit(127);
    }
    if(*type == 'r'){
        close(pdf[1]);
        if((fp = fdopen(pdf[0],type)) == NULL)
            return (NULL);
        else{
            close(pdf[0]);
            if((fp = fdopen(pdf[1],type)) == NULL)
                return (NULL);
        }
        childpid[fileno(fp)] = pid;
        return (fp);
    }

}
