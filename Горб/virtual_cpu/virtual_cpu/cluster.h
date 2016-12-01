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
public:
	TCluster(int _size);
	~TCluster();
	TCluster(int _size, int _num_cores);
	virtual void PrintStatus();
	virtual void SetFreq(const int _freq);
	void SetStat(int _cpu,int _core);
	virtual int SeeFreq() const { return set[0].SeeFreq(); }
	virtual int SeeCores() const;
	void SetComplex(int _cpu, int _core, int _complex);
	int SeeSize() const { return size; }
	virtual int Check(int _cpu, int _core);
	int CheckAll();
	int SeeCorePerCPU() const { return set[0].SeeCores(); }
	bool IsBusy(int _cpu,int _core) const;
	TCpu& operator[](int i);
};



#endif