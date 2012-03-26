/* This contains the class definitions */
/* Most of the functions explain themselves via their names */
#include <iostream>
using namespace std;
#include "parallelclasses.h"
/* Effectively a NULL Worker */
Worker::Worker():r(0),c(0),workerGrid(0)
{

}
/* Instantiation of a Worker with rows, columns, and a worker size matrix */
Worker::Worker(int row, int col, int **grid):r(row),c(col)
{
	workerGrid = new int *[r];
	for(int i=0;i<r;i++)
		workerGrid[i] = new int [c];
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			workerGrid[i][j]=grid[i][j];
		}
	}
	
	/* This is where a worker does its work */
	/* This code detects the largest integer in the row or column and changes every other entry to 0*/
	int holder=0;
	if(c>r)
	{
		for(int i=0;i<r;i++)
		{
			for(int j=0;j<c;j++)
			{
				if(holder<workerGrid[i][j])
					holder=workerGrid[i][j];
			}
			for(int j=0;j<c;j++)
			{
				if(workerGrid[i][j]<holder)
					workerGrid[i][j]=0;
			}
				holder=0;
		}
	}
	else
	{
		for(int j=0;j<c;j++)
		{
			for(int i=0;i<r;i++)
			{
				if(holder<workerGrid[i][j])
					holder=workerGrid[i][j];
			}
			for(int i=0;i<r;i++)
			{
				if(workerGrid[i][j]<holder)
					workerGrid[i][j]=0;
			}
			holder=0;
		}
	}
}
/* Prints Matrix of a Worker */
void Worker::printGrid()
{
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			cout << workerGrid[i][j] << " ";
		}
		cout << endl;
	}
}
/* Returns the workers matrix to whoever calls this function (also a bit dodgy programmatically)*/
int **Worker::getGrid()
{
	return workerGrid;
}
/* This became extraneous after it was pretty much absorbed by the Worker constructor
void Worker::runWorker(int item)
{
	int place;
	if ((item-1)<(r*c)){
		place=(item%c)-1;
		item/=c;
		cout << workerGrid[place][item] << endl;
	}
}
*/
/* Frees up memory and destructs a Worker */
Worker::~Worker()
{
	for(int i=0;i<r;i++)
		delete [] workerGrid[i];
	delete [] workerGrid;
}
/* Effectively a NULL Master */
Master::Master():r(0),c(0),numOfWorkers(0),masterGrid(0)
{

}
/* Nice and simple creation/construction of a Master from 2 ints and a 2D int array (or double pointer) */
Master::Master(int row, int col, int workerNum, int **grid):r(row),c(col),numOfWorkers(workerNum)
{
	masterGrid = new int *[r];
	for(int i=0;i<r;i++)
		masterGrid[i] = new int [c];
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			masterGrid[i][j]=grid[i][j];
		}
	}
}
/* Simply prints Master's matrix */
void Master::printGrid()
{
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			cout << masterGrid[i][j] << " ";
		}
		cout << endl;
	}
}
/* can be used to change the number of workers */
void Master::setNumberOfWorkers(int num)
{
	numOfWorkers=num;
}
/* This creates all the workers and gives them their data to work on. This function decides what way the workers should be oriented based upon the number of them and the number of rows and columns in the Master's matrix */
void Master::runWorkers()
{
	arrayWorker = new Worker *[numOfWorkers];
	int **tempGrid=0;
	/* if for column workers */
	if(c%numOfWorkers==0)
	{
		cout << "Workers created with respect to columns" << endl;
		int workerColNum;
		workerColNum=c/numOfWorkers;
		tempGrid = new int *[r];
		for(int i=0;i<r;i++)
			tempGrid[i] = new int [workerColNum];
			
		for(int workerIt=0;workerIt<numOfWorkers;workerIt++)
		{
			for(int i=0;i<r;i++)
			{
				for(int j=(workerIt*workerColNum);j<workerColNum+(workerIt*workerColNum);j++)
				{
					tempGrid[i][j-(workerIt*workerColNum)]=masterGrid[i][j];
				}
			}
			arrayWorker[workerIt] = new Worker(r,workerColNum,tempGrid);
		}
		for(int i=0;i<r;i++)
			delete [] tempGrid[i];
		delete [] tempGrid;
	}

	/* else create row workers */
	else
	{
		cout << "Workers created with respect to rows" << endl;
		int workerRowNum;
		workerRowNum=r/numOfWorkers;
		tempGrid = new int *[workerRowNum];
		for(int i=0;i<workerRowNum;i++)
			tempGrid[i] = new int [c];
		
		for(int workerIt=0;workerIt<numOfWorkers;workerIt++)
		{
			for(int i=(workerIt*workerRowNum);i<workerRowNum+(workerIt*workerRowNum);i++)
			{
				for(int j=0;j<c;j++)
				{
					tempGrid[i-(workerIt*workerRowNum)][j]=masterGrid[i][j];
				}
			}
			arrayWorker[workerIt] = new Worker(workerRowNum,c,tempGrid);
		}
		for(int i=0;i<workerRowNum;i++)
			delete [] tempGrid[i];
		delete [] tempGrid;
		
	}
	
}
/* This function calls each Worker's getGrid() function in order to return the worked upon data to the Master. It puts each Worker's data back in the correct place in the original matrix. */
void Master::getWorkers()
{
	int **tempGrid=0;
	if(c%numOfWorkers==0)
	{
		int workerColNum;
		workerColNum=c/numOfWorkers;
		for(int workerIt=0;workerIt<numOfWorkers;workerIt++)
		{
			tempGrid=arrayWorker[workerIt]->getGrid();
			for(int i=0;i<r;i++)
			{
				for(int j=(workerIt*workerColNum);j<workerColNum+(workerIt*workerColNum);j++)
				{
					masterGrid[i][j] = tempGrid[i][j-(workerIt*workerColNum)];
				}
			}
			arrayWorker[workerIt] = new Worker(r,workerColNum,tempGrid);
		}
	}
	else
	{
		int workerRowNum;
		workerRowNum=r/numOfWorkers;
		for(int workerIt=0;workerIt<numOfWorkers;workerIt++)
		{
			tempGrid=arrayWorker[workerIt]->getGrid();
			for(int i=(workerIt*workerRowNum);i<workerRowNum+(workerIt*workerRowNum);i++)
			{
				for(int j=0;j<c;j++)
				{
					masterGrid[i][j]=tempGrid[i-(workerIt*workerRowNum)][j];
				}
			}
		}
	}
	tempGrid=0;
}
/* Returns a 2D integer array (**int) (COMMENT: This is the function I have qualms about but currently it's simplest way of spitting out the matrix in an alterable form) */ 
int **Master::getGrid()
{
	return masterGrid;
}
/* Deletion and destruction of Master class with respect to memory managment */
Master::~Master()
{
	for(int i=0;i<r;i++)
		delete [] masterGrid[i];
	delete [] masterGrid;
	/*for(int i=0;i<numOfWorkers;i++)
		delete [] arrayWorker[i];
	delete [] arrayWorker;*/
}
