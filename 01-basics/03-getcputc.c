#include "00-apue.h"

int main()
{
    int  c;
    while((c = getc(stdin)) != EOF && c != '\n')
        if(putc(c,stdout)  == EOF)
            err_sys("out_put  error");

    if(ferror(stdin))
        err_sys("input error");
    if(c == '\n')
        err_sys("THNAK OU!!!");

    exit(0);
}
