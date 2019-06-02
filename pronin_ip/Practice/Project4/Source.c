#include <stdio.h>
#include <locale.h>
#define N 100
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
void main()
{
	setlocale(LC_ALL, "Russian");
	int a[N];
	int n, i;
	printf("¬ведите размер массива");
	scanf_s("%d", &n);
	printf("¬ведите массив");
	for (i = 0; i < n; i++)
		scanf_s("%d", &a[i]);
	choose(a, n);
	for (i = 0; i < n; i++)
		printf("%d", a[i]);
}