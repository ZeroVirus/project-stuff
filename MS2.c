#include <stdio.h>
#include <pthread.h>

/* This is our thread function.  It is like main(), but for a thread */
int j=0;//worker id
int sum=0;//total array sum
pthread_mutex_t mymutex;
int ary[10][10]={

{1,11,21,9,41,51,61,71,2,91},
{2,12,1,82,42,0,66,11,82,7},
{45,2,23,33,14,53,63,73,83,93},
{4,14,24,34,44,54,64,74,5,94},
{5,76,25,64,45,55,65,75,85,95},
{6,16,26,36,46,56,56,76,86,96},
{7,17,27,37,47,57,67,77,87,96},
{42,33,28,38,48,58,68,93,88,98},
{9,19,29,28,49,59,39,88,89,99},
{10,20,30,40,50,60,70,80,90,100}

};
//sum of row 1 is: 359
//sum of row 2 is: 305
//sum of row 3 is: 482
//sum of row 4 is: 411
//sum of row 5 is: 590
//sum of row 6 is: 500
//sum of row 7 is: 519
//sum of row 8 is: 594
//sum of row 9 is: 508
//sum of row 10 is: 550
//total sum should be: 4818

void *threadFunc(void *arg)
{
	char *str;
	int i = 0;
	int subsum=0;

	str=(char*)arg;
	
	
	while(i < 10)
	{
		subsum+=ary[j][i];
		//usleep(1);
		printf("Worker %d says: %s\n",j+1,str);
		++i;
	}
	sum+=subsum;
	printf("The sum of row %d is: %d\n",j+1,subsum);
	pthread_exit(NULL);
	return NULL;
}

int main(void)
{
	pthread_mutex_init(&mymutex, NULL);
	pthread_t pth;	// this is our thread identifier
	int i = 0;
	
	while(j<10)
	{
		/* Create worker thread */
		
		pthread_create(&pth,NULL,threadFunc,"adding up the array...");
		
		//Lock the semaphore
		//pthread_mutex_lock(&mymutex);

		/* wait for our thread to finish before continuing */
		pthread_join(pth, NULL /* void ** return value could go here */);

		j++;

		//Unlock the semaphore
		//pthread_mutex_unlock(&mymutex);
	}
	
	printf("The sum of the entire array is %d\n",sum);
	pthread_exit(NULL);
	return 0;
}

