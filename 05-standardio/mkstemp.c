#include "00-apue.h"
#include <errno.h>


void make_temp(char *teplate);

int main()
{
    char good_template[] = "/tmp/dirXXXXXX";
    char *bad_template="/tmp/dirXXXXXX";

    printf("string to create first temp file \n");
    make_temp(good_template);
    printf("string to create second temp file \n");
    make_temp(bad_template);
    exit(0);

}

void make_temp(char *template)
{
    int fd;
    struct stat sbuf;
    if((fd = mkstemp(template)) < 0)
        err_sys("cannot create temp file");
    printf("temp name = %s\n",template);
    close(fd);
    if(stat(template,&sbuf) < 0) {
        if(errno == ENOENT)
            printf("file doesn't exist.");
        else
            err_sys("stat failed");
    }else{
        printf("file exists.");
        unlink(template);
    }

}
