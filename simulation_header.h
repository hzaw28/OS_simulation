/*
*	File Name				:	simulation_header.h
*	Primary Author			:	Hein Htet Zaw
*	Contributing Author(s)	:	
*	Date Created			:	26 April 2016
*	Date Last Modified		:	29 April 2016
*	
*	Description		:	This is the header file where all the global variables and data structures
*						are declared and defined.
*	
*/

#ifndef _SIMULATION_HEADER_H_
#define _SIMULATION_HEADER_H_

#include <string>
#include <array>

#define long_max 60
#define short_max 30
#define io_max 30
#define cpu_burst_max 25

		//set up a structure for jobs
struct job {

				//include the following information in the job
	int num;						//job number
	int length;						//(CPU bursts + I/O bursts) time
	int arrival;					//arriaval time
	int io_burst;					//the length of time this job requires an I/O device
	int cpu_burst[cpu_burst_max];	//the time this process requires the CPU
	int burst_count = 0;			//number of cpu bursts given in the data file

				//create variables for the followings

	int time_in_cpu = 0;		//total time spent in the CPU
	int time_in_longQ = 0;		//total time spent in the Long Term Queue
	int time_in_shortQ = 0;		//total time spent in the Short Term Queue
	int time_in_ioQ = 0;		//total time spent in the I/O Queue
	int turnaround = 0;			//the turnaround time
	int response = 0;			//the response time
	int switching = 0;			//time spent in context switching

	job *left;
	job *right;
};

			//declare and define STORAGE *This is a binary tree*
class tree {
private:
	job *root;
	int jobCount;

public:
	tree() { root = NULL; jobCount = 0;};		//create constructor function
	bool add(job *theJob);						//add the items in the tree, sorted by **JOB NUMBER**

	job * getJob(int JobNum);					//get the pointer of a certain job by its job number
	job * getRoot() { return root; };			//get the root of "this" tree

	int getJobCount() { return jobCount; };		//get the number of jobs in "this" tree

};

		//declare and define the long queue and its required functions
class longQueue {
private:
	int front, rear, size;
	job *theQ[long_max];

public:
	longQueue() { front = -1; rear = -1; size = 0; };							//construct the object
	bool isEmpty() { if (size == 0) return true; else return false; };			//returns empty or not
	bool isFull() { if (size == long_max) return true; else return false; };	//returns full or not
	
	bool add(job *);					//adds the given job
	job * getNext();					//get the pointer of the next job in the queue

	int getRear() { return rear; };		//returns the array number of lsatmost node
	int getFront() { return front; };	//returns the array number of frontmost node
	int getSize() { return size; };		//returns the current number of jobs in the queue
};

		//declare and define short queue and its required functions
class shortQueue {
private:
	int front, rear, size;
	job *theQ[short_max];

public:
	shortQueue() { front = -1; rear = -1; size = 0; };							//constructs the object
	bool isEmpty() { if (size == 0) return true; else return false; };			//returns empty or not
	bool isFull() { if (size == short_max) return true; else return false; };	//returns full or not

	bool add(job *);					//adds the given job
	job * getNext();					//get the pointer of the next job in the queue

	int getRear() { return rear; };		//returns the array number of lsatmost node
	int getFront() { return front; };	//returns the array number of frontmost node
	int getSize() { return size; };		//returns the current number of jobs in the queue
};

		//declare and define the required functions for I/O queue
class ioQueue {
private:
	int front, rear, size;
	job *theQ[io_max];

public:
	ioQueue() { front = -1; rear = -1; size = 0; };								//constructs the object
	bool isEmpty() { if (size == 0) return true; else return false; };			//returns empty or not
	bool isFull() { if (size == io_max) return true; else return false; };		//returns full or not

	bool add(job *);					//adds the given job
	job * getNext();					//get the pointer of the next job in the queue

	int getRear() { return rear; };		//returns the array number of lsatmost node
	int getFront() { return front; };	//returns the array number of frontmost node
	int getSize() { return size; };		//returns the current number of jobs in the queue
};

			//declare and instantiate global variables and arrays
			//create spaces for the followings

static job *processor = NULL;				//the (only) processor
static job *IO = NULL;						//the I/O device

			//declare variables for the followings
static int myClock = 0;						//clock to keep track of time
static int LTQ_time = 0;					//total long term queue wait time for all jobs
static int STQ_time = 0;					//total short term queue wait time for all jobs
static int IOQ_time = 0;					//total I/O Queue wait time for all jobs

static job *temp = NULL;					//temporary space

						//*** more variables are to be added as needed ***//

#endif // !_SIMULATION_HEADER_H_
