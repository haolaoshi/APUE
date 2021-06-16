#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void unlock( void * arg )
{
   pthread_mutex_unlock( &lock );
}

void * function( void * arg )
{
    printf("begin\n");
   while( 1 )
   {
      pthread_mutex_lock( &lock );
      pthread_cleanup_push( &unlock, NULL );

      /*
       Any of the possible cancellation points could
       go here.
      */
      pthread_testcancel();

      pthread_cleanup_pop( 1 );
   }
}

int main()
{
    int err;
    pthread_t tid;
    
    err = pthread_create(&tid,NULL,function,(void*)1);
    if(err != 0)
        printf("error when create thread \n");
    sleep(1);
   exit(0); 
}
