#include "00-apue.h"
#include <sys/wait.h>



int main()
{
    pid_t pid;
    if((pid = fork()) < 0)
        err_sys("error fork");
    else if(pid == 0){
        if((pid = fork()) < 0)
            err_sys("error fork");
        else if(pid > 0)
            exit(0); 
/*        printf("WE'RE THE SECOND CHILD,OUR PARENT BECOMES INIT AS SOON\n");
        printf("AS OUR REAL PARENT CLAS EXIT() INT THE STATEMENT ABOVE.\n");
        printf("WE'RE DONE,INIT WILL REAP OUR STATUS\n");
*/
        sleep(2);

        printf("second child[%ld] , parent ppid = %ld\n",(long)getpid(),(long)getppid());

        printf("\n");
        exit(0);
    }

    if(waitpid(pid,NULL,0) != pid)
        err_sys("error waitpid ");
/*    
    printf("We're the parent (the original process); we continue executing,\n");
    printf("knowing that we're not the parent of the second child.");
*/
    exit(0);

}
