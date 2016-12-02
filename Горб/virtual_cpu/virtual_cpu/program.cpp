#include "program.h"

TProg::TProg() : TCluster(1)
{
	complex = 1;
	count = 1;
	task = new double[count];
	srand(time(0));
	task[0] = rand() % RANDO;
	active = false;
}

TProg::~TProg()
{
	delete[] task;
}

TProg::TProg(const int _count, int _size, int _cores) : TCluster(_size, _cores)
{
	if (_count<1 ||_count > max_t_count) throw ("Fail. PC will be overdrived or invalid value");
	count = _count;
	complex = 1;
	task = new double[count];
	srand(time(0));
	for (register int i = 0; i < count; i++)
		task[i] = rand() % RANDO;
	active = false;
}

TProg::TProg(const int _count, const int _complex, int _size, int _cores) : TCluster(_size, _cores)
{
	if (_count<1 || _count > max_t_count) throw ("Fail. PC will be overdrived because of too big count or invalid value");
	if (_complex < 1 || _complex > max_t_complex) throw ("Fail. PC will be overdrived because of too big complex of task or invalid value");
	count = _count;
	complex = _complex;
	task = new double[count];
	srand(time(0));
	for (register int i = 0; i < count; i++)
		task[i] = rand() % RANDO;
	active = false;
}

void TProg::SetComplex(int _complex)
{
	if (_complex<1 ||_complex > max_t_complex) throw ("Fail. PC will be overdrived because of too big complex of task");
	complex = _complex;
}

void TProg::SetCount(int _count)
{
	if (_count<1 ||_count > max_t_count) throw ("Fail. PC will be overdrived because of too big count");
	count = _count;
	task = new double[count];
	srand(time(0));
	for (register int i = 0; i < count; i++)
		task[i] = rand() % RANDO;
}

bool TProg::Process()
{
	active = true;
	double speed = 1000/SeeFreq();
	int size_clust = SeeSize();
	int percpu = SeeCorePerCPU();
	tact = err = completes = 0;
	bool gotcha = false;
	TQueue<double> work(QUEUE);
	srand(time(0)); //toggle randomizer
	while (active)
	{
		for (register int i = 0; i < count*complex || !work.IsEmpty(); i++, tact++)  //main cycle 
		{
			if (i < count)
			{
				alpha = double(rand()) / (RAND_MAX*(2 - 0) + 0); // alhpa == ( 0 <= a < 2 )
				if (alpha > 1)
				{
					//err++;
					break;
				}//alpha must be (0 <= a < 1)
				if (!work.IsFull()) //if queue is not full push task into, else denial of service
				{
					work.Push(task[i]); //load task
					cache = work.GetCount();
										//find free core:
					gotcha = false;
					for (register int p = 0; p < size_clust; p++)
					{
						for (register int t = 0; t < percpu; t++)
						{
							if (!IsBusy(p, t))
							{
								SetStat(p, t);
								SetLeftTact(p, t, complex);
								p = size_clust;
								t = percpu;
								gotcha = true;
							}
						}
					}//end find free core

					 //if free core exist:
					if (gotcha) work.Pop();
					else i--; //else wait (free cycle) - decrease iterator of cycle
				}
				else { err++; }
			}
			if (i >= count*complex && !work.IsEmpty())
			{
				gotcha = false;
				for (register int p = 0; p < size_clust; p++)
				{
					for (register int t = 0; t < percpu; t++)
					{
						if (!IsBusy(p, t))
						{
							SetStat(p, t);
							SetLeftTact(p, t, complex);
							p = size_clust;
							t = percpu;
							gotcha = true;
						}
					}
				}//end find free core

				 //if free core exist:
				if (gotcha) work.Pop();
				else i--;
			}
			completes += CheckAll(); //count of complete tasks
			Sleep(speed);


		}
		active = false;
		cache = work.GetCount();
	}
	//PrintResults();
	return true;
}

void TProg::Stop()
{
	while (!_kbhit());
	active = false;
	PrintStatus();
	PrintResults();
	
}

void TProg::PrintResults()
{
	printf("\n Results of calculations:\n");
	printf("\n\n Current status of CPU's:");
	printf("\n Size of Cluster: %i\n Count of cores: %i\n Total cores: %i", SeeSize(), SeeCorePerCPU(), SeeCores());
	//PrintStatus();
	printf("\n Size of cache tasks: %i", cache);
	printf("\n Count of completed tasks: %.0f", completes);
	printf("\n Count of denial of service: %.0f", err);
	printf("\n Count of used cluster's tacts: %.0f\n", tact);
}