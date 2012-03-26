#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/file.h>

void slave(int row, int column, int array[row][column], FILE *file);
void parent();

int main(int argc, char* argv[]) {
	row = argv[1];             // New addition
	column = argv[2];          // New Addition
	val = argv[3];             // New Addition 
	if (remove("somefile2.txt") != 0)
		printf("Error removing file.");
	else
		printf("File remove succesfully.");
	FILE *somefile;                           // New Add
	somefile = fopen("somefile2.txt","a");    // New Add
	pid_t pid;
	int i=0,j,k,l=0;	
	int array[row][col];
	for (j=0;j<row;j++) {
		for (k=0;k<column;k++) {
			array[j][k] = va;;
		}
	}
	
		for (i;i<row;i++) {	
			if ((pid = fork()) == 0)
				slave(i,column,array,somefile); 
			else
				parent();
	}

	return 0;
}

void slave(int row, int column, int array[row][column],FILE *some) { /*Child function splits the array into rows and*/ 
	int k,l,sum=0,lockt;								  /*individually adds up the sum of the rows when it is called*/
	FILE* file=some;
	for (k=0;k<column;k++) {
		sum += array[row][k];	
		printf("%d\n",sum);
	}
	printf("I am the slave.\n");
	//file = fopen("somefile2.txt","a");
	fprintf(file,"%d\n",sum);
	fclose(file);	
	exit(0);
	return;
}

void parent() { /*Adds up total using the results from child*/
	FILE* newfile;
	char *a; int i,total; char buffer[1024]; int newbuf;
	newfile = fopen("somefile2.txt","r");
	while ( fgets(buffer,1024,newfile) > 0 ) {
		sscanf(buffer,"%d",&newbuf);
		printf("%d\n",newbuf);
	}
	fclose(newfile);	
	printf("I am the parent.\n");
}

char* child_reverse_string(char *string) {
	  int end= strlen(string)-1;
	  int start = 0;
	  while(start<end)
	  {
	    string[start] ^= string[end];
	    string[end] ^= string[start];
	    string[start]^= string[end];
	    ++start;
	    --end;
	  }
	  return string;
}
