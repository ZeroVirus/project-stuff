#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>

void child(int row, int column, int array[row][column]);
//void child(int *, int, int);
int parent();

int main() {
	int array[2][2];
	int i,row =2 ,column =2;
	//somearray = (int **)array;
	while (i<2) {
		fork();
		child(2,2,array);
		i++;
	}
//	parent();
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
	fprintf(file,"%c\n",sum);
	fclose(file);	
}

/*
int parent() {
	FILE* newfile;
	newfile = fopen("somefile2.txt","r");
	while (newfile != EOF) {
		
	}
	
}
*/