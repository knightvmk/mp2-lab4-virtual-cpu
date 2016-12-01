#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "program.h"

#define scanf scanf_s
#define _CRT_SECURE_NO_WARNINGS

#define NTHREADS 2

DWORD WINAPI Process(void *arg)
{
	printf("SIGNAL THREAD ONE - PROCESS\n");
	//z.Process();
	return 0;
}

DWORD WINAPI Stop(void *arg)
{
	printf("SIGNAL THREAD TWO - STOP\n");
	//z.Stop();
	return 0;
}

void main()
{
	system("color 3F");
	system("title Virtual calculations by cluster system");
	//-------it's invalid somthing non understandable thing-------//
	DWORD idThread;
	HANDLE *h;
	h = new HANDLE[2];
	h[0] = CreateThread(0, 0, Stop, 0, 0, &idThread);
	h[1] = CreateThread(0, 0, Process, 0, 0, &idThread);
	WaitForMultipleObjects(2, h, TRUE, INFINITE);
	delete[] h;
	//-------end of non understandable things-------//
	printf("\nEnd of handles\n");
	//---simple block----//
	double count_cpu, size_cluster, task_complex, count_tasks;
	printf("\n Enter size of cluster system: ");
	scanf("%lf", &size_cluster);
	printf("\n Enter the number of processor cores: ");
	//may be setup a freq of cpus
	scanf("%lf", &count_cpu);
	printf("\n Enter complexity of the task. Value of complexity means the amount spent CPU tacts: ");
	scanf("%lf", &task_complex);
	printf("\n Enter count of tasks: ");
	scanf("%lf", &count_tasks);
	TProg TASK(count_tasks, task_complex, size_cluster, count_cpu);
	printf("\n Do you want the process your task?\n Press any key:");
	system("pause");
	TASK.Process();
	TASK.PrintResults();
	system("pause");
	
}

