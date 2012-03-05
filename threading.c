#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 500

int sum=0;
enum {numberofelements=5000};
int asd[numberofelements];
pthread_mutex_t mymutex=PTHREAD_MUTEX_INITIALIZER; //semaphore
int fakeevent=0; //fake event type object used to make sure the printf runs at end of threads execution

void *threadfunc(void *threadid)
{
    long tid;
    int psum=0;
    int i;

    tid = (long)threadid;
    printf("Thread #%i starting\n", tid);
    for(i=tid*10;i<(tid+1)*10;i++){
        psum+=asd[i];
    }
    pthread_mutex_lock(&mymutex);
    sum+=psum;
    fakeevent++;
    pthread_mutex_unlock(&mymutex);
    printf("Thread #%i exiting\n", tid);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;

    for(t=0;t<numberofelements;t++){
        asd[t]=t+1;
    }
    for(t=0;t<NUM_THREADS;t++){
        printf("Main-creating thread %i\n", t);
        rc = pthread_create(&threads[t], NULL, threadfunc, (void *)t);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    while(1){
        if(fakeevent==NUM_THREADS){
            printf("The sum is %i\n", sum);
            break;
        }
    }

    pthread_exit(NULL);
}
