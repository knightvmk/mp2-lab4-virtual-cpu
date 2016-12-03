#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include "program.h"

#define scanf scanf_s
#define _CRT_SECURE_NO_WARNINGS

TProg task(1,1,1); // global initialization of task

DWORD WINAPI Stop(void *arg)
{
	task.Stop();
	return 0;
}
void main()
{
	setlocale(LC_ALL, "Rus");
	system("color 3F");
	system("title Эмуляция работы кластерной многоядерной системы");
	DWORD idThread;
	HANDLE *h;
	h = new HANDLE;
	double task_complex, count_tasks, time;
	int count_cpu, size_cluster, cpu_freq;
	bool done = false;
	clock_t start, fine;
	printf("\n Введите размер кластера. Размер кластера означает количество процессоров.\n Размер должен быть больше 0 и меньше %i", max_size);
	do
	{
		printf("\n:: ");
		scanf("%i", &size_cluster);
	} while (size_cluster<1 || size_cluster>max_size);
	task.SetSize(size_cluster);
	printf("\n Введите количество ядер процессора.\n Значение должно быть больше 0 и меньше %i", max_cores);
	do
	{
		printf("\n:: ");
		scanf("%i", &count_cpu);
	} while (count_cpu<1 || count_cpu>max_cores);
	task.SetCores(count_cpu);
	printf("\n Введите значение рабочей частоты процессора в МГц.\n Минимальное значение : [ %i ], Максимальное значение : [ %i ]", min_freq, max_freq);
	do
	{
		printf("\n:: ");
		scanf("%i", &cpu_freq);
	} while (cpu_freq<min_freq || cpu_freq>max_freq);
	task.SetFreq(cpu_freq);
	printf("\n Введите сложность задачи. Значение характеризует количество требуемых тактов для решения одной задачи\n");
	printf("Значение должно быть больше 0 и менее  %i", max_t_complex);
	do
	{
		printf("\n:: ");
		scanf("%lf", &task_complex);
	} while (task_complex<1 || task_complex>max_t_complex);
	task.SetComplex(task_complex);
	printf("\n Введите количество задач / процессов. Максимальное количество: [ %i ]", max_t_count);
	do
	{
		printf("\n:: ");
		scanf("%lf", &count_tasks);
	} while (count_tasks<1 || count_tasks>max_t_count);
	task.SetCount(count_tasks);
	system("cls");
	printf("====================================================\n\n");
	printf(" Текущее количество процессоров: %i\n", size_cluster);
	printf(" Текущее количество ядер в одном процессоре: %i\n", count_cpu);
	printf(" Общее количество ядер: %i\n", count_cpu*size_cluster);
	printf(" Текущая частота процессоров в кластере: %i МГц\n\n", cpu_freq);
	printf(" Текущая сложность задачи: %.0lf\n", task_complex);
	printf(" Текущее количество задач / процессов: %0.lf\n\n", count_tasks);
	printf("====================================================\n\n");
	printf("\n Нажмите любую клавишу дла начала загрузки кластера\n\n");
	printf(" Замечание: \n Если вы желаете прервать (закончить) процесс и посмотреть статистику нажмите [ Enter ] в процессе выполнения\n");
	system("pause");
	h[0] = CreateThread(0, 0, Stop, 0, 0, &idThread);
	printf("\n\n Выполнение процессов...\n");
	start = clock();
	done = task.Process();
	fine = clock();
	time = double(fine - start) / CLOCKS_PER_SEC;
	if (done)
	{
		task.PrintResults();
		printf("\n Общее время вычислений: %.3lf секунд\n", time);
	}
	WaitForMultipleObjects(2, h, TRUE, INFINITE);
	delete[] h;
	Sleep(1500);
	printf("\n Выход любой клавишей. . .\n\n");
	system("pause");
}

