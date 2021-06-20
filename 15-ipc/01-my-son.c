#include "00-apue.h"


int main()
{
    int n;
    int fd[2];
    int pid;
    char line[MAXLINE];


    if(pipe(fd) < 0)
        err_sys("error when pipe");

    if((pid = fork() ) < 0)
        err_sys("error when fork");
    else if(pid > 0){
        close(fd[0]);
        char des[MAXLINE];
        sprintf(des,"hello world %ld",(long)getpid());
        write(fd[1],des,12);
    }else {
        close(fd[1]);
        n = read(fd[0],line,MAXLINE);
        char des[MAXLINE];
        sprintf(des,"pid = %ld \t%s",(long)getpid(),line);
        
        write(STDOUT_FILENO,line,n);
    }
    exit(0);
}
