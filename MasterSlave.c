#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/file.h>

void slave(int row, int column, int array[row][column]);
void parent();

int main() {
	pid_t pid;
	int i=0,row =3 ,column =3,j,k,l=0;	
	int array[3][3];
	for (j=0;j<row;j++) {
		for (k=0;k<column;k++) {
			array[j][k] = 2;
		}
	}
	
		for (i;i<row;i++) {	
			if ((pid = fork()) == 0)
				slave(i,3,array); 
			else
				parent();
	}
	
	return 0;
}

void slave(int row, int column, int array[row][column]) { /*Child function splits the array into rows and*/ 
	int k,l,sum=0,lockt;								  /*individually adds up the sum of the rows when it is called*/
	FILE* file;
	for (k=0;k<column;k++) {
		sum += array[row][k];	
		printf("%d\n",sum);
	}
	printf("I am the slave.\n");
	file = fopen("somefile2.txt","a");
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
