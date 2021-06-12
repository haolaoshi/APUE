#include "00-apue.h"
//ADVANCED PROGRAMMING Unix Enviroment
int globvar = 6;

char buf[] = "a write to stdout\n";

int main()
{
    int var;
    pid_t pid;

    var = 88;

    if(write(STDOUT_FILENO,buf,sizeof(buf) - 1) != sizeof(buf) - 1)
        err_sys("write_error");
    printf("before fork\n");


    if((pid = fork()) < 0){
        err_sys("fork error");
    }
    else if(pid == 0){
        printf("CHILD\t");
        globvar++;
        var++;
    }else {
        printf("FATHER\t");
        sleep(2);
    }
    printf("pid = %ld, glob = %d, var = %d \n",(long)getpid(),globvar,var);

    exit(0);
}
