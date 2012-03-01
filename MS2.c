#include <stdio.h>
#include <pthread.h>

/* This is our thread function.  It is like main(), but for a thread */
int sum=0;
int ary[]={1,11,21,9,41,51,61,71,2,91
	   2,12,1,82,42,0,66,11,82,7
	   45,2,23,33,14,53,63,73,83,93
	   4,14,24,34,44,54,64,74,5,94
           5,76,25,64,45,55,65,75,85,95
           6,16,26,36,46,56,56,76,86,96
           7,17,27,37,47,57,67,77,87,96
	   42,33,28,38,48,58,68,93,88,98
	   9,19,29,28,49,59,39,88,89,99
           10,20,30,40,50,60,70,80,90,100};


void *threadFunc(void *arg)
{
	char *str;
	int i = 0;
	

	str=(char*)arg;
	
	
	while(i < 11 )
	{
		sum+=ary[i];
		usleep(1);
		printf("threadFunc says: %s\n",str);
		++i;
	}
	
	return NULL;
}

int main(void)
{
	
	pthread_t pth;	// this is our thread identifier
	int i = 0;

	/* Create worker thread */
	pthread_create(&pth,NULL,threadFunc,"adding up the array...");

	/* wait for our thread to finish before continuing */
	pthread_join(pth, NULL /* void ** return value could go here */);

	while(i < 11 )
	{
		usleep(1);
		printf("Master is using usleep() to allow for next worker to partake in addition...\n");
		++i;
	}
	printf("The sum of the array is %d\n",sum);
	return 0;
}

