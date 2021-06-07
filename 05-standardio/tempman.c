#include "00-apue.h"

int main()
{
    char name[L_tmpnam],line[MAXLINE];
    FILE *fp;
    printf("%s\n",tmpnam(NULL));
    tmpnam(name);

    printf("%s\n",name);
    if((fp = tmpfile()) == NULL) 
        err_sys("one line of output\n",fp);
    fputs("one line of output\n",fp);
    rewind(fp);
    if(fgets(line,sizeof(line),fp) == NULL)
        err_sys("gets error");
    fputs(line,stdout);
    exit(0);
}
