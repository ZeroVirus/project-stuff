#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/file.h>

void child(int row, int column, int array[row][column]);
void parent();

int main() {
	pid_t pid;
	int i=0,row =2 ,column =2,j,k,l=0;	
	int array[2][2];
	for (j=0;j<2;j++) {
		for (k=0;k<2;k++) {
			array[j][k] = 1;
		}
	}
	
	//while (i<2) {
		for (i;i<row;i++) {	
			if (pid = fork())
				child(i,2,array); 
			else
				parent();
		//i++;
	}
	//child(0,2,array);
	//child(1,2,array);
	
	return 0;
}

void child(int row, int column, int array[row][column]) { /*Child function splits the array into rows and*/ 
	int k,l,sum=0,lockt;								  /*individually adds up the sum of the rows when it is called*/
	FILE* file;
	for (k=0;k<column;k++) {
		sum += array[row][k];	
		printf("%d\n",sum);
	}
	printf("I am the child.\n");
	file = fopen("somefile2.txt","w");
	fprintf(file,"%d\n",sum);
	fclose(file);	
	exit(0);
		return;
}

void parent() { /*Adds up total using the results from child*/
	FILE* newfile;
	char *a; int i; char buffer[1024];
	newfile = fopen("somefile2.txt","r");
	/*while ( fgets(buffer,1024,newfile) > 0 )
		printf("%s",buffer);*/
	
	printf("I am the parent.\n");
}
