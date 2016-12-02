#include "cluster.h"

TCluster::TCluster(int _size) //single core
{
	if (_size<1 || _size>max_size) throw ("Fail. Cluster is overdrive");
	size = _size;
	set = new TCpu[size];
}

TCluster::~TCluster()
{
	delete[] set;
	set = 0;
}

TCluster::TCluster(int _size, int _num_cores) //multi core
{
	if (_size<1 || _size>max_size) throw ("Fail. Cluster is overdrive");
	if (_num_cores<1 || _num_cores>max_num_cores) throw ("Fail. Cluster is overdrive due to max num cores");
	size = _size;
	set = new TCpu[size];
	for (register int i = 0; i < size; i++)
		set[i].SetCore(_num_cores);
}

void TCluster::SetFreq(const int _freq)
{
	if (_freq<min_freq || _freq>max_freq) throw ("Fail. Invalid value of frequency");
	for (register int i = 0; i < size; i++)
	{
		set[i].SetFreq(_freq);
	}
}

void TCluster::SetStat(int _cpu, int _core)
{
	set[_cpu].SetStat(_core);
}

int TCluster::SeeCores() const
{
	return (size*(set[0].SeeCores()));
}

void TCluster::SetSize(int _size)
{
	if (_size<1 || _size>max_size) throw ("Fail. Invalid input value of size");
	delete[] set;
	size = _size;
	set = new TCpu[size];
	for (register int i = 0; i < size; i++)
		set[i].SetCore(SeeCorePerCPU());
}

void TCluster::SetCores(int _num_cores)
{
	if (_num_cores<1 || _num_cores>max_num_cores) throw ("Fail. Invalid input value of num cores");
	for (register int i = 0; i < size; i++)
		set[i].SetCore(_num_cores);
}

void TCluster::SetLeftTact(int _cpu, int _core, int _complex)
{
	set[_cpu].SetLeftTact(_core, _complex);
}

int TCluster::Check(int _cpu, int _core)
{
	if (!IsBusy(_cpu, _core)) return 0; //0 - not busy
	else
	{
		if (set[_cpu].Check(_core) == 1) return 1; //task is done
		else return 0; //task is not done
	}
}

int TCluster::CheckAll()
{
	int res = 0;
	for (register int i = 0; i<size; i++)
		for (register int j = 0; j < SeeCorePerCPU(); j++)
		{
			if (Check(i, j) == 1) res++; // increase count of completed tasks
		}
	return res;
}

void TCluster::PrintStatus()
{
	printf("\n");
	printf(" Current frequency: %i MHz\n", SeeFreq());
	for (register int i = 0; i < size; i++)
	{
		printf("\n CPU No_%i :\n", i);
		set[i].PrintStatus();
	}
}

bool TCluster::IsBusy(int _cpu, int _core) const
{
	return set[_cpu].IsBusy(_core);
}