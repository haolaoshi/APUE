#include "00-apue.h"
#include <fcntl.h>
#define FILE_MODE DEFFILEMODE
#include "14-TELL.c"

int lock_reg(int fd,int cmd,int type,off_t offset,int whence,off_t len)
{
    struct flock lock;
    lock.l_type = type;
    lock.l_start= offset;
    lock.l_whence = whence;
    lock.l_len = len;

    return (fcntl(fd,cmd,&lock));
}

pid_t lock_test(int fd,int type,off_t offset,int whence,off_t len)
{
    struct flock lock;
    lock.l_type = type;
    lock.l_start = offset;
    lock.l_whence = whence;
    lock.l_len = len;
    if(fcntl(fd,F_GETLK,&lock) < 0)
        err_sys("fcntl error");
    if(lock.l_type == F_UNLCK)
        return (0);

    return (lock.l_pid);

}

static void lockabyte(const char *name,int fd,off_t offset)
{
    if(writew_lock(fd,offset,SEEK_SET,1) < 0)
        err_sys("%s: writew_lcok error",name);
    printf("%s: got the lock , tyte %lld\n",name,(long long)offset);
}

int main()
{
    int fd;
    pid_t pid;

    if((fd = creat("templock",FILE_MODE)) < 0)
        err_sys("creat error");
    if(write(fd,"ab",2) != 2)
        err_sys("write error");

    TELL_WAIT();
    if((pid = fork())< 0)  
        err_sys("fork error");
    else if(pid == 0){
        locable("child",fd,0);
        TELL_PARENT(getppid());
        WAIT_PARENT();
        locakabyte("child",fd,1);
    }else{
        lockabyte("parent",fd,1);
        TELL_CHILD(pid);
        WAIT_CHILD();
        locakabyte("parent",fd,0);
    }

    exit(0);
}
