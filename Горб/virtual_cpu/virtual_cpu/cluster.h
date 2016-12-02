#ifndef __CLUSTER_H__
#define __CLUSTER_H__

#include <stdio.h>
#include "cpu.h"

const size_t max_size = 10;
const size_t max_num_cores = 10;

class TCluster
{
private:
	size_t size; //size of cpus
	TCpu* set;
protected:
	int CheckAll();
	bool IsBusy(int _cpu, int _core) const;
	virtual int Check(int _cpu, int _core);
	virtual void SetLeftTact(int _cpu, int _core, int _complex);
	void SetStat(int _cpu, int _core);
public:
	TCluster(int _size);
	~TCluster();
	TCluster(int _size, int _num_cores);
	virtual void PrintStatus();
	virtual void SetFreq(const int _freq);
	virtual int SeeFreq() const { return set[0].SeeFreq(); }
	virtual int SeeCores() const;
	void SetSize(int _size);
	void SetCores(int _num_cores);
	int SeeSize() const { return size; }
	int SeeCorePerCPU() const { return set[0].SeeCores(); }
};



#endif