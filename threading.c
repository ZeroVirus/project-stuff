#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//USER DEFINED GLOBAL VARIABLES
enum {numberofelements=10000,NUM_THREADS=50};
char string[]="DEVIL MAY CRY";

//global variables
int sizeofstring=0;
int sum=0;
int asd[numberofelements];//array that will be summed
pthread_mutex_t mymutex=PTHREAD_MUTEX_INITIALIZER; //semaphore
int fakeevent=0; //fake event type object

//Summation function
void *worker_sum(void *threadid)
{
    long tid;
    int psum=0;
    int i;

    tid = (long)threadid;
    printf("Sum thread #%li starting\n", tid);

    //Chunks of the array that will be summed is allocated to each worker based on the ratio
    //of number of elements to threads.
    for(i=tid*(numberofelements/NUM_THREADS);i<(tid+1)*(numberofelements/NUM_THREADS);i++){
        psum+=asd[i];
    }

    //semaphore while accessing sum variable and a fake event counter
    pthread_mutex_lock(&mymutex);
    sum+=psum;
    fakeevent++;
    pthread_mutex_unlock(&mymutex);

    printf("Sum thread #%li exiting\n", tid);

    pthread_exit(0);
}

void *worker_reversestring(void *threadid)
{
    long tid;
    char temp;

    tid = (long)threadid;
    printf("Reverse thread #%li starting\n", tid);

    //Reverses string
    temp=string[tid];
    string[tid]=string[sizeofstring-1-tid];
    string[sizeofstring-1-tid]=temp;

    //Increment fake event counter and printf statement
    pthread_mutex_lock(&mymutex);
    printf("Current status of string: %s\n",string);
    fakeevent++;
    pthread_mutex_unlock(&mymutex);

    printf("Reverse thread #%li exiting\n", tid);

    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int rc;

//***Sum of numbers***//    
    long t=0;

    //Initialize array
    for(t=0;t<numberofelements;t++){
        asd[t]=t+1;
    }

    //creates threads and executes summation function
    for(t=0;t<NUM_THREADS;t++){
        printf("Main-creating thread %li to sum array.\n", t);
        rc = pthread_create(&threads[t], NULL, worker_sum, (void *)t);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    //Event to print out the final sum only after all threads have finished
    while(1){
        if(fakeevent==NUM_THREADS){
            printf("The sum is %i\n", sum);
            break;
        }
    }

//***Reverse String***//
    
    fakeevent=0;//reset fake event counter
    
    //Finds size of given string
    int x=0;
    while(string[x]){
        sizeofstring++;
        x++;
    }

    for(t=0;t<sizeofstring/2;t++){
        printf("Main-creating thread %li to reverse string.\n", t);
        rc = pthread_create(&threads[t], NULL, worker_reversestring, (void *)t);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    //Event to print out the final sum only after all threads have finished
    while(1){
        if(fakeevent==sizeofstring/4){
            printf("The reversed string is %s\n", string);
            break;
        }
    }

    pthread_exit(NULL);
    return 0;
}
