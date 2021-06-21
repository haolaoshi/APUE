#include "00-apue.h"

static int pdf1[2],pdf2[2];

void TELL_WAIT()
{

    if(pipe(pdf1) < 0 || pipe(pdf2) < 0)
        err_sys("error pipe");



}

void TELL_PARENT(pid_t pid)
{
    if(write(pdf2[1],"c",1) != 1)
        err_sys("write error");

}

void WAIT_PARENT()
{
    char c;

    if(read(pdf1[0],&c,1) != 1)
        err_sys("eror read");

    if(c != 'p')
        err_quit("error data : wait _prent");

}

void TELL_CHILD(pid_t pid)
{
    if(write(pdf1[1],"p",1) != 1)
        err_sys("error write");


}

void WAIT_CHILD()
{
    char c;
    if(read(pdf2[0],&c,1) != 1)
        err_sys("read error");

    if(c != 'c')
        err_sys("WAIT CHILD error data");
}
