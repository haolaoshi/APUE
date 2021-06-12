#include <stdlib.h>
#include <stdio.h>

int main(int argc , char* argv[])
{

    if(argc == 1 ) 
        perror("failed\n");

    char b[100];

    char *p = getenv(argv[1]);
    int i = 0;
    if(p == NULL) 
        perror("failed\n");
    

    printf("%d, %s\n",i,b);

}
