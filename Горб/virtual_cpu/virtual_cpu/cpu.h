#ifndef __CPU_H__
#define __CPU_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


struct ker_stat
{
	bool stat;
	int left_tact = 0;
};

const size_t max_cores = 10;
const size_t min_freq = 800;
const size_t max_freq = 5000;

class TCpu
{
private:
	size_t freq; //Mhz
protected:
	size_t core; //count of cores
	ker_stat* cores; //stat cores
	//size_t tacts=0;
public:
	TCpu();
	~TCpu();
	TCpu(int _cores);
	TCpu(const TCpu &a);
	bool IsBusy(int i) const;
	void SetStat(const int _core);
	virtual int SeeFreq() { return freq; }
	virtual void SetFreq(const int _freq);
	virtual void SetLeftTact(int _core, int _left);
	void SetCore(const int _core);
	virtual int Check(int _core);
	virtual int SeeCores() { return core; };
	virtual void PrintStatus(); //for all cores
};
#endif
