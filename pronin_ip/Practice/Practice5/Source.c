#include <stdio.h>
#include <locale.h>
#define N 10
void choose(int a[], int n)
{
	int i, j, min, minind;
	for (i = 0; i < n; i++)
	{
		min = a[i];
		minind = i;
		for (j = i + 1; j < n; j++)
		{
			if (a[j] < min)
			{
				min = a[j];
				minind = j;
			}
		}
		a[minind] = a[i];
		a[i] = min;
	}
}
void insert(int a[], int n)
{
	int i, j, tmp;
	for (i = 0; i < n; i++)
	{
		j = i - 1;
		tmp = a[i];
		while ((j >= 0) && (a[j] > tmp))
		{
			a[j + 1] = a[j];
			a[j] = tmp;
			j--;
		}
	}
}
void bubble(int a[], int n)
{
	int i, j, tmp;
	for (i = 0; i < n; i++)
	{
		for (j = 1; j < n; j++)
		{
			if (a[j - 1] > a[j])
			{
				tmp = a[j];
				a[j] = a[j-1];
				a[j - 1] = tmp;
			}
		}
	}
}
void countingsord(int a[], int n)
{
	int i, j, b=0;
	int count[N] = { 0 };
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (a[j] == i)
				count[i]++;
		}
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < count[i]; j++)
		{
			a[b] = i;
			b +=1;
		}
	}
}
void main()
{
	setlocale(LC_ALL, "Russian");
	int a[N];
	int i, mode, n=6;
	do
	{
		printf("Введите массив");
		for (i = 0; i < n; i++)
			scanf("%d", &a[i]);
		printf("Выберите вариант сортировки:\n");
		printf("Введите 1 для сортировки выбором\n");
		printf("Введите 2 для сортировки вставками\n");
		printf("Введите 3 для пузырьковой сортировки\n");
		printf("Введите 4 для сортировки подсчетом (диапазон от чисел 0-5)\n");
		printf("Введите 5 для выхода из программы\n");
		scanf("%d", &mode);
		switch (mode)
		{
		case 1:
		{
			choose(a, 6);
			for (i = 0; i < n; i++)
				printf("%d", a[i]);
			break;
		}
		case 2:
		{
			insert(a, 6);
			for (i = 0; i < n; i++)
				printf("%d", a[i]);
			break;
		}
		case 3:
		{
			bubble(a, 6);
			for (i = 0; i < n; i++)
				printf("%d", a[i]);
			break;
		}
		case 4:
		{
			countingsord(a, 6);
			for (i = 0; i < n; i++)
				printf("%d", a[i]);
			break;
		}
		case 5:
		{
			return;
		}
		}
	} while (mode != 5);
}

