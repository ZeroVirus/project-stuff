/* Includes */
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */
#include <semaphore.h>  /* Semaphore */




/* prototype for worker thread routine */
void workerjob ( void *ptr );

/* global vars */
/* semaphores are declared global so they can be accessed
   in main() and in thread routine,
   here, the semaphore is used as a mutex */
unsigned long x = 0;
unsigned char c;
char str[]="DEVIL RATS ON NO STAR LIVE";



sem_t mutex;


int main()
{
    int size=strlen(str);
    int i[2];
    pthread_t worker;
    //pthread_t thread_b;

    i[0] = 0; /* argument to threads */
    i[1] = 1;

    sem_init(&mutex, 0, 1);      /* initialize mutex to 1 - binary semaphore */
                                 /* second param = 0 - semaphore is local */
    printf("String is initially: %s \n", str);
    /* Note: you can check if thread has been successfully created by 	         checking return value of pthread_create */
    for (x = 0; x < (size / 2); ++x)
    {
         pthread_create (&worker, NULL, (void *) &workerjob, (void *) &i[0]);
         pthread_join(worker, NULL);
    }
    sem_destroy(&mutex); /* destroy semaphore */
    printf("After being reversed, string is: %s \n", str);
    /* exit */
    return 1;
    exit(0);
} /* main() */

void workerjob ( void *ptr )
{
    int size=strlen(str);
    
    sem_wait(&mutex);       /* down semaphore */
    /* START CRITICAL REGION */
    c = str[(size - 1)- x];
    str[(size - 1) - x] = str[x];
    str[x] = c;
    printf("String is now: %s \n", str);
    /* END CRITICAL REGION */
    sem_post(&mutex);       /* up semaphore */

    pthread_exit(0); /* exit thread */
}
