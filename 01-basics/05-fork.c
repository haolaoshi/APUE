#include <stdio.h>
#include "00-apue.h"
#include <stdlib.h>
#include <sys/wait.h>


int main()
{
    char command_line[1024];
    pid_t pid;
    int status;

    printf("%% ");
    while(fgets(command_line,1024,stdin) != NULL){
        if(command_line[strlen(command_line) - 1] == '\n')
            command_line[strlen(command_line) - 1] = 0;

        if((pid = fork()) < 0){
            err_sys("fork error.");
        }else if(pid == 0) {
           execlp(command_line,command_line,(char*) 0);
           err_ret("couldn't execute: %s " , command_line);
           printf("%s-->%s\n",command_line,strerror(errno));
           perror(command_line);
           exit(127);
        }

        printf("Father %ld, child %ld \n",(long)getpid(),(long)pid);
        
        if((pid = waitpid(pid,&status, 0)) < 0)
            err_sys("waitpid error");
        printf("%% ");

    }
    exit(1);

}
