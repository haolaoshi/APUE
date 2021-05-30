#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("uid = %d, git = %d \n",getuid(),getgid());
    exit(0);
}
