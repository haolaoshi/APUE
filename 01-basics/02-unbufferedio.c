#include "00-apue.h"


#define BUFFSIZE     4096

int main()
{
    int n;
    char buf[BUFFSIZE];
    while(( n = read(STDIN_FILENO,buf,BUFFSIZE)) > 0)
        if(write(STDOUT_FILENO,buf,n) != 0)
            err_sys("write_error.");
    if(n < 0)
        err_sys("read error");

    exit(0);
}
