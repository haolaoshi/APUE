#include "00-apue.h"


int globvar = 6;

int main()
{
    int var;
    pid_t pid;

    var = 88;
    printf("before vfork.\n");
    if((pid = vfork()) < 0){
        err_sys("vfork error");
    }else if(pid == 0){
        printf("CHILD\t");
        globvar++;
        var++;
    printf("pid= %ld,glob = %d,var = %d\n",(long)getpid(),globvar,var);
        _exit(0);

    }
    sleep(1);
    printf("FATHER\tpid= %ld,glob = %d,var = %d\n",(long)getpid(),globvar,var);

    exit(0);
}
