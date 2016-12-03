#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <locale.h>
#include "queue.h"
#include "cluster.h"

#define RANDO 18000000
#define QUEUE 20

//----x86----//
//-primitive-//

const size_t max_t_count = INT_MAX; 
const size_t max_t_complex = 64;

class TProg : public TCluster
{
private:
	int complex; // need tacts
	int count; // count of tasks
	double* task; // array for tasks and results
	double alpha; // chance of new task
	double completes = 0; // count of completed tasks
	double err = 0; //count of uncompleted tasks
	double true_err = 0;
	double tact = 0; //count of used tacts
	bool active; //if prog is calculates - true, if stopped - false;
	bool ready = false;
	int cache = 0; //number of tasks in queue
public:
	TProg();
	TProg(const int _count, int _size, int _cores);
	TProg(const int _count, const int _complex, int _size, int _cores);
	~TProg();
	void SetComplex(int _complex);
	void SetCount(int _count);
	bool Process();
	void Stop();
	void PrintResults();
};

#endif
