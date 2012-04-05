/* This file implements the Master and Worker classes and then times their operation */

#include <iostream>
#include <fstream>
#include "parallelclasses.h";
using namespace std;
#include <time.h>
int main(int argc, char *argv[])
{
	int rows, columns, workers;
	rows = 11;
	columns = 10;
	workers = 11;
	int **mainGrid = 0;
	mainGrid = new int *[rows];
	for(int i=0;i<rows;i++)
	{
		mainGrid[i] = new int [columns];
	}
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<columns;j++)
		{
			mainGrid[i][j] = 2;
		}
	}

	/* Timing starts here */
	clock_t start, end;

	/*cout << "Create Master:\n\n";*/
	start = clock();
	Master timeMaster(rows,columns,workers,mainGrid);
	end = clock();
	long elapsed = (end-start);
	cout << "\nMaster: " << elapsed << " milliseconds.\n";

	/*cout << "Generate and run Workers:\n\n";*/
	start = clock();
	timeMaster.runWorkers();
	end = clock();
	elapsed = (end-start);
	cout << "Worker: " << elapsed << " milliseconds.\n";

/*	cout << "Return the finished work to the Master:\n";*/
	start = clock();
	timeMaster.getWorkers();
	end = clock();
	elapsed = (end-start);
	cout << "Return " << elapsed << " milliseconds.\n";

	/* timeMaster.printGrid(); */


	for(int i=0;i<rows;i++)
	{
		delete [] mainGrid[i];
	}
	delete [] mainGrid;

	return 0;
}
