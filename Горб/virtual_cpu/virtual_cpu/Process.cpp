#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "program.h"

#define scanf scanf_s
#define _CRT_SECURE_NO_WARNINGS

#define NTHREADS 2
#define SLP 100

TProg task(1,1,1);

DWORD WINAPI Process(void *arg)
{
	//printf("SIGNAL THREAD TWO - PROCESS\n");
	task.Stop();
	return 0;
}

/*DWORD WINAPI Stop(void *arg)
{
	printf("SIGNAL THREAD ONE - STOP\n");
	
	return 0;
}*/

void main()
{
	system("color 3F");
	system("title Virtual calculations by cluster system");
	//-------it's invalid somthing non understandable thing-------//
	DWORD idThread;
	HANDLE *h;
	h = new HANDLE;
	//h[1] = CreateThread(0, 0, Stop, 0, 0, &idThread);

	//-------end of non understandable things-------//
	printf("\nEnd of handles\n");
	//---simple block----//
	double task_complex, count_tasks;
	int count_cpu, size_cluster, cpu_freq;
	bool done = false;
	printf("\n Enter size of cluster system.\n Value must be larger than 0 and less than %i", max_size);
	do
	{
		printf("\n:: ");
		scanf("%i", &size_cluster);
	} while (size_cluster<1 || size_cluster>max_size);
	task.SetSize(size_cluster);
	printf("\n Enter the number of processor cores.\n Value must be larger than 0 and less than %i", max_cores);
	do
	{
		printf("\n:: ");
		scanf("%i", &count_cpu);
	} while (count_cpu<1 || count_cpu>max_cores);
	task.SetCores(count_cpu);
	printf("\n Enter the value of the CPU frequencies in MHz. Min Value is %i, Max Value is %i", min_freq, max_freq);
	do
	{
		printf("\n:: ");
		scanf("%i", &cpu_freq);
	} while (cpu_freq<min_freq || cpu_freq>max_freq);
	task.SetFreq(cpu_freq);
	printf("\n Enter complexity of the task. Value of complexity means the amount spent CPU tacts.\n");
	printf("Value must be more than 1 and less than %i", max_t_complex);
	do
	{
		printf("\n:: ");
		scanf("%lf", &task_complex);
	} while (task_complex<1 || task_complex>max_t_complex);
	task.SetComplex(task_complex);
	printf("\n Enter count of tasks. Max value is %i", max_t_count);
	do
	{
		printf("\n:: ");
		scanf("%lf", &count_tasks);
	} while (count_tasks<1 || count_tasks>max_t_count);
	task.SetCount(count_tasks);
	system("cls");
	printf("====================================================\n\n");
	printf("Current count of CPUs: %i\n", size_cluster);
	printf("Current number of cores in processor: %i\n", count_cpu);
	printf("Total amount of cores: %i\n", count_cpu*size_cluster);
	printf("Current frequency of processors: %i MHz\n\n", cpu_freq);
	printf("Corrent complexity of a one task: %.0lf\n", task_complex);
	printf("Current amout of tasks: %0.lf\n\n", count_tasks);
	printf("====================================================\n\n");
	printf("\n Press anykey if you want the process your task\n");
	printf("Notice: if you want terminate process of calculating press anykey after start\n");
	system("pause");
	h[0] = CreateThread(0, 0, Process, 0, 0, &idThread);
	printf("\n\n Calculating...\n");
	done = task.Process();
	if (done)
	{
		task.PrintResults();
		system("pause");
		exit(1);
	} else
	WaitForMultipleObjects(2, h, TRUE, INFINITE);
	//TASK.Process();
	//TASK.PrintResults();
	//WaitForMultipleObjects(2, h, TRUE, INFINITE);
	system("pause");
	delete[] h;
}

