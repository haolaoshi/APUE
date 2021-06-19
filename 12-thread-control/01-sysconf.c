#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>



int main()
{
    long destr = sysconf(PTHREAD_DESTRUCTOR_ITERATIONS);
    long keys = sysconf(PTHREAD_KEYS_MAX);
    long stacks = sysconf(PTHREAD_STACK_MIN);
//    long max = sysconf(PTHREAD_THREADS_MAX); 
    int    max = 0;
    printf("%ld,%ld,%ld\n",destr,keys,stacks);
    exit(0);
}
