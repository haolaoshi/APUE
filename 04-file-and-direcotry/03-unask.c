#include "00-apue.h"
#include <fcntl.h>

#define RWRWRW  (S_IRUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
int main()
{
    umask(0);
    if(creat("foo",RWRWRW) < 0)
        err_sys("create error for foo 1");
    umask(S_IRGRP|S_IWGRP |S_IROTH| S_IWOTH);
    if(creat("bar",RWRWRW) < 0)
        err_sys("create error for bar 2");
    exit(0);
}
