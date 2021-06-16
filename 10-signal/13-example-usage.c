#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void catch_function(int signo)
{
    puts("Interactive attention signal caught.");
}

int main()
{
    if(signal(SIGINT,catch_function) == SIG_ERR){
        fputs("An error occurred while setting a signal handler.",stderr);
        return EXIT_FAILURE;
    }
    sleep(5);
    puts("Rasing the interactive attention signal.");
    if(raise(SIGINT) != 0){
        fputs("Error raising the signal.\n",stderr);
        return EXIT_FAILURE;
    }
    puts("Exiting.");
    return EXIT_SUCCESS;
}
