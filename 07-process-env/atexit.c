#include <stdio.h>
#include <stdlib.h>


static void my_exit();
static void my_exit2();

int main()
{
    if(atexit(my_exit2) != 0){
        printf("cannot register my_exit2\n");
        exit(1);
    }
    if(atexit(my_exit) != 0){
        printf("cannot register my_exist\n");
        exit(2);
    }
    if(atexit(my_exit) != 0){
        printf("this is my done.\n");
        return (0);
    }

}

static void my_exit()
{
    printf("first exit handler\n");

}

static void my_exit2()
{
    printf("second exit handler\n");

}
