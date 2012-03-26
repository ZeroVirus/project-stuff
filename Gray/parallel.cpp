/* Patrick Gray */
/* Parallel Matrix Alteration 2 */
#include <iostream>
#include <fstream>
#include "parallelclasses.h"
using namespace std;

int main()
{
/*	These variables are for general input and data retention */
	int rows, columns, workers;
	int **mainGrid=0;
/*	Input */
	cout << "How many rows are in the matrix?" << endl;
	cin >> rows;
	cout << "How many columns are in the matrix?" << endl;
	cin >> columns;
	cout << "How many workers do you want the Master to generate for alteration? \n(Note: with current implementation, please only use a number of workers that will evenly divide the number of items in the matrix)" << endl;
	cin >> workers;

/*	Create a matrix with the given parameters */

	mainGrid = new int *[rows];
	for (int i=0;i<rows;i++)
		mainGrid[i]=new int [columns];

/*	Get values for each entry */
	for(int i=0;i<rows;i++){
		for(int j=0;j<columns;j++){
			cout << "Please enter the number for [" << i << "][" << j << "]" << endl;
			cin >> mainGrid[i][j];
		}
	}
	
	cout <<endl;

/*	Display entered matrix for convenience */
	for(int i=0;i<rows;i++){
		for(int j=0;j<columns;j++){
			cout << mainGrid[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;
/*	Creates a Master with the data previously input by the user */
	Master newMaster(rows,columns,workers,mainGrid);
/*	Run (execute/start) the workers */
	newMaster.runWorkers();
/*	Get (return/collect) the workers */
	newMaster.getWorkers();
/*	Print the altered matrix */
	newMaster.printGrid();



/*	Create the output file */
	ofstream myfile;
	myfile.open("output.txt");
/*	Insert original input and delete original **mainGrid with memory in mind */
	myfile << "Original Matrix:\n";
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<columns;j++)
		{
			myfile << mainGrid[i][j] << " ";
		}
		myfile << "\n";
		delete [] mainGrid[i];
	}
	delete [] mainGrid;

/*	Get the Master's altered matrix and insert into the output file */
	int **outputGrid=newMaster.getGrid();
	myfile << "\nAltered Matrix:\n";
	for(int i=0;i<rows;i++)
	{
		for(int j=0;j<columns;j++)
		{
			myfile << outputGrid[i][j] << " ";
		}
		myfile << "\n";
	}
	myfile.close();
	
	return 0;
}
