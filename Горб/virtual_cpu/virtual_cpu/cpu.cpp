#include "cpu.h"

TCpu::TCpu() //single core
{
	freq = min_freq;
	core = 1;
	cores = new ker_stat[core];
	cores[0].stat = false;
}

TCpu::~TCpu()
{
	delete[] cores;
	cores = 0;
}

TCpu::TCpu(int _cores) //multi core
{
	freq = min_freq;
	core = _cores;
	cores = new ker_stat[core];
	for (register int i = 0; i < core; i++)
		cores[i].stat = false;
}

TCpu::TCpu(const TCpu &a)
{
	freq = a.freq;
	core = a.core;
	cores = new ker_stat[core];
	for (register int i = 0; i < core; i++)
		cores[i].stat = a.cores[i].stat;
}

bool TCpu::IsBusy(int i) const
{
	if (i < 0 || i >= core) throw ("Fail. Invalid iterator");
	return cores[i].stat;
}

void TCpu::SetStat(const int _core)
{
	if (_core >= core) throw ("Fail. Invalid core iterator");
	if (cores[_core].stat) cores[_core].stat = false;
	else
		cores[_core].stat = true;
}

void TCpu::SetFreq(const int _freq)
{
	if (_freq > max_freq || _freq < min_freq)
		throw("Fail. Impossible value of freq");
	else freq = _freq;
}

void TCpu::SetLeftTact(int _core, int _left)
{
	cores[_core].left_tact = _left;
}

void TCpu::SetCore(const int _core)
{
	if (_core > max_cores) throw ("Fail. Too much count of cores");
	core = _core;
	delete[] cores;
	cores = new ker_stat[core];
	for (register int i = 0; i < core; i++)
		cores[i].stat = false;

}

int TCpu::Check(int _core)
{
if (!IsBusy(_core)) return 0; //0 - not busy
	else
	{
		if (cores[_core].left_tact != 0)
		{
			cores[_core].left_tact--;
			if(cores[_core].left_tact!=0)
			return 0; //task is not done
			else
			{
				SetStat(_core);
				return 1;
			}
		}
		else
		{
			SetStat(_core);
			return 1; //task is done
		}
	}
}

void TCpu::PrintStatus()
{
	for (register int i = 0; i < core; i++)
	{
		if (IsBusy(i)) printf(" Core %i is busy\n", i);
		else printf(" Core %i is free\n", i);
	}
}
