/* This contains the class declarations for parallel matrix alteration */

class Worker
{
public:
	Worker();
	Worker(int, int, int **);
	void printGrid();
	int **getGrid();
	/* void runWorker(int); */
	~Worker();
private:
	int r,c;
	int **workerGrid;
};

class Master
{
public:
	Master();
	Master(int, int, int, int **);
	void printGrid();
	void setNumberOfWorkers(int);
	void runWorkers();
	void getWorkers();
/*	DISCLAIMER: I really don't like the function getGrid() because I'm pretty sure it isn't really a good programming practice when using an object oriented style.
	I only returned the private member because I needed to create the output file with it and had no other way of accessing it.  */
	int **getGrid();
	~Master();
private:
	int r,c,numOfWorkers;
	int **masterGrid;
	Worker **arrayWorker;
};

