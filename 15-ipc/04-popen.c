#include "00-apue.h"
#include <sys/wait.h>


#define PAGER "${PAGER:-more}"


int main(int argc,char* argv[])
{

    char line[MAXLINE];
    FILE *fpin,*fpout;

    if(argc != 2)
        err_sys("error argument .: a.out <pathname>");

    if((fpin = fopen(argv[1],"r")) == NULL)
        err_sys("error oepn file ");

    if((fpout = popen(PAGER,"w")) == NULL)
        err_sys("error write open");

    while(fgets(line,MAXLINE,fpin) != NULL){
        if(fputs(line,fpout) == EOF)
            err_sys("fputs error to pipe");
    }

    if(ferror(fpin))
        err_sys("error fgets");
    if(pclose(fpout) == -1)
        err_sys("pclose error");
    exit(0);
}
