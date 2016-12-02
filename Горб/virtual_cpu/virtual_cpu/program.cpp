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
	double speed = 1000/double(SeeFreq());
	int size_clust = SeeSize();
	int percpu = SeeCorePerCPU();
	tact = err = completes = 0;
	bool gotcha = false;
	TQueue<double> work(QUEUE);
	srand(time(0)); //toggle randomizer
		for (register int i = 0; i < count*complex || !work.IsEmpty(); i++, tact++)  //main cycle 
		{
			if (!active) //if process terminated then fully return
			{
				ready = false;
				return false; //process isnt ready
			}
			if (i < count)
			{
				alpha = double(rand()) / RAND_MAX; // alhpa == ( 0 <= a < 1 )
				if (alpha > 0.92)
				{
					true_err++;
					continue;
				} //alpha must be (0 <= a < 0.92)
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
	ready = true;
	return true;
}

void TProg::Stop()
{
	if (ready) return;
	char c;
	c = _getch();
	if (c == 13)
	{
		if (ready) return;
		active = false;
		system("cls");
		printf("\n\n Îïåðàöèÿ áûëà ïðåðâàíà!\n\n");
		PrintStatus();
		PrintResults();
	} else
	Stop();
}

void TProg::PrintResults()
{
	setlocale(LC_ALL, "Rus");
	printf("\n Ðåçóëüòàòû âû÷èñëåíèé:\n");
	printf("\n Ðàçìåð êëàñòåðà: %i\n Êîëè÷åñòâî ÿäåð: %i\n Îáùåå êîëè÷åñòâî ÿäåð: %i", SeeSize(), SeeCorePerCPU(), SeeCores());
	printf("\n Âñåãî ñîçäàííûõ ïðîöåññîâ: %i", count);
	printf("\n Êîëè÷åñòâî êýøèðîâàííûõ ïðîöåññîâ: %i", cache);
	printf("\n Êîëè÷åñòâî íå ïîÿâèâøèõñÿ ïðîöåññîâ: %0.f", true_err);
	printf("\n Êîëè÷åñòâî âûïîëíåííûõ ïðîöåññîâ: %.0f", completes);
	printf("\n Êîëè÷åñòâî ïðîöåññîâ ñ îòêàçîì: %.0f", err);
	printf("\n Êîëè÷åñòâî çàòðà÷åííûõ òàêòîâ: %.0f\n", tact);
}
