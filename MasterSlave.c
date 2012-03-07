#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>

void child(int row, int column, int array[row][column]);
//void child(int *, int, int);
void parent();

int main() {
	pid_t pid;	
	int array[2][2];
	int i,row =2 ,column =2;
	while (i<2) {
		if (pid = fork())
			child(2,2,array);
		else
			parent();
		
		i++;
	}
	return 0;
}

void child(int row, int column, int array[row][column]) {
	int k,sum=0;
	for (k=0;k<2;k++) {
		sum += array[row][k];	
	}
	printf("I am the child.\n");
	FILE* file;
	file = fopen("somefile2.txt","a+");
	fprintf(file,"%d\n",sum);
	fclose(file);	
	exit(0);
}

void parent() {
	FILE* newfile;
	char *a; int i; char buffer[1024];
	newfile = fopen("somefile2.txt","r");
	while ( fgets(buffer,1024,newfile) > 0 )
		printf("%s",buffer);
	
	printf("I am the parent.");
}
