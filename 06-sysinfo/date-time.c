#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{
    time_t t;
    struct tm *tmp;
    char buf1[16];
    char buf2[64];

    //time(&t);
    t = time(NULL);

    tmp = localtime(&t);
    if(strftime(buf1,16,"time and date: %r, %a %b %d, %Y",tmp) == 0)
        printf("buffer length 16 is too smarll \n");
    else
        printf("%s\n",buf1);

    if(strftime(buf2,64,"time and date: %r,%a %b  %d , %Y",tmp) == 0)
        printf("buffer length 54 is too small \n");
    else
        printf("%s\n",buf2);
    exit(0);
}
