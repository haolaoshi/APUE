#include "00-apue.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(int argc,char* argv[])
{
    int fd;
    pid_t pid;
    char buf[5];
    struct stat statbuf;

    if(argc != 2){
        fprintf(stderr,"usage : %s filename \n",argv[0]);
        exit(1);
    }

    if((fd = open(argv[1],O_RDWR|O_CREAT|O_TRUNC,FILE_MODE)) < 0)
        err_sys("error open");
    if(write(fd,"abcdefg",6) != 6)
        err_sys("error write");

    if(fstat(fd,&statbuf) < 0)
        err_sys("fstat error");
    if(fchmod(fd,(statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
        err_sys("fchmod error");

    TELL_WAIT();
    if((pid = fork()) < 0)
        err_sys("fork error");
    else if(pid > 0){
        if(write_lock(fd,0,SEEK_SET,0) < 0)
            err_sys("error write lock");
        TELL_CHILD(pid);
        if(waitpid(pid,NULL,0) < 0)
            err_sys("error wait pid");
    }else{

        WAIT_PARENT();
        set_fl(fd,O_NONBLOCK);
        if(read_lock(fd,0,SEEK_SET,0) != -1) 
            err_sys("succ when read slock ");
        printf("read lock of already locked region returnr %d\n",errno);

        if(lseek(fd,0,SEEK_SET) == -1)
            err_sys("error when lseek");
        if(read(fd,buf,2) < 0)
            error_ret("read failed ( mandator locking workds");
        else
            printf("read ok ,no mandatoriy locking , buf = %2.2s\n",buf);

    }
    exit(0);

}
