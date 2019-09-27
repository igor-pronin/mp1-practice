#define _CRT_SECURE_NO_WARNINGS
#define UNICODE
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <locale.h>
#include <time.h>
#include <locale.h>
#define MAX_LEN 4048//макс длина для строк
#define ROFL 2000
#define MAX_FILES 1000//предположительное количество файлов
int kolvo = 0;//количество файлов
#define K 150//для сортировки подсчетом

void Merge(int *a, ULONGLONG *size, int l, int m, int r) //слияние
{
	int i, j = m + 1, h, tmp;
	ULONGLONG tmp1;
	for (i = l; ((i < r) && (j <= r)); i++)
	{
		if (size[a[i]] > size[a[j]])//сравнение размеров
		{
			tmp = a[j];
			for (h = j; h > i; h--)
				a[h] = a[h - 1];
			a[i] = tmp;//замена индексов
			j++;
		}
	}
}
void MergeSort(int *a, ULONGLONG *size, int l, int r)//разбиение
{
	int m;
	if (l >= r) return;
	m = (l + r) / 2;
	MergeSort(a, size, l, m);
	MergeSort(a, size, m + 1, r);
	Merge(a, size, l, m, r);
}
void anihilation(ULONGLONG*filesize, ULONGLONG*filesizecopy, int* filesindex, int* newindex, int kolvo)//обнуление перед сортировкой
{
	int i;
	for (i = 0; i < kolvo; i++)
	{
		filesize[i] = filesizecopy[i];
		newindex[i] = filesindex[i];

	}
}
int ListDirectoryContents(const wchar_t *sDir, ULONGLONG*filesize, wchar_t **fileNames)//вывод списка файлов
{
	int i = 0;
	WIN32_FIND_DATA fdFile;
	HANDLE hFind = NULL;
	wchar_t *sPath;
	sPath = (wchar_t*)malloc(ROFL * sizeof(wchar_t));
	wsprintf(sPath, L"%s\\*.*", sDir);
	if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Путь не найден: [%s]\n", sDir);
		return 1;
	}
	do
	{
		if (wcscmp(fdFile.cFileName, L".") != 0 && wcscmp(fdFile.cFileName, L"..") != 0)
		{
			ULONGLONG fileSize = fdFile.nFileSizeHigh;
			fileSize <<= sizeof(fdFile.nFileSizeHigh) * 8;
			fileSize |= fdFile.nFileSizeLow;
			filesize[i] = fileSize;
			fileNames[i] = (wchar_t*)malloc(ROFL * sizeof(wchar_t));
			wsprintf(sPath, L"%s\\%s", sDir, fdFile.cFileName);
			wsprintf(fileNames[i], L"%s", sPath);
			i++;
			kolvo++;
		}
	} while (FindNextFile(hFind, &fdFile));
	FindClose(hFind);
	return 0;
}
// Обмен значений целочисленных переменных
void swap_int(int *var1, int *var2)
{
	int tmp = *var1;
	*var2 = (*var1 = *var2, tmp);
}

// Обмен значений 64-битных переменных
void swap_ULL(ULONGLONG *var1, ULONGLONG *var2)
{
	ULONGLONG tmp = *var1;
	*var2 = (*var1 = *var2, tmp);
}
int find_by_size(ULONGLONG size, int k, ULONGLONG *sizes, int n)
{
	int i = 0, fnd = 0, idx = -1;
	if (k > n)
		return -2;
	while ((i < n) && (fnd < k))
	{
		if (sizes[i] == size)
		{
			idx = i;
			fnd++;
		}
		i++;
	}
	if ((i == n) && (idx == -1))
		return -1;
	return idx;
}
void bubble(ULONGLONG* filesize, int *newindex, int kolvo)//сортировка пузырьком
{
	int i, j;
	for (i = 0; i < kolvo; i++)
		for (j = 1; j < kolvo - i; j++)
			if (filesize[newindex[j - 1]] > filesize[newindex[j]])
				swap_int(newindex + j, newindex + j - 1);
}
void insert(ULONGLONG* filesize, int *newindex, int kolvo)//сортировка вставками
{
	int i, j;
	ULONGLONG temp;
	for (i = 1; i < kolvo; i++)
	{
		temp = filesize[newindex[i]];
		j = i - 1;
		while ((j >= 0) && (filesize[newindex[j]] > temp))
		{
			newindex[j + 1] = newindex[j];
			newindex[j] = i;
			j--;
		}
	}
}
void choose(ULONGLONG* filesize, int kolvo, int* newindex)//сортировка выбором
{
	int i, j, minind;
	ULONGLONG min;
	for (i = 0; i < kolvo; i++)
	{
		min = filesize[newindex[i]];
		minind = i;
		for (j = i + 1; j < kolvo; j++)
			if (filesize[newindex[j]] < min)
			{
				min = filesize[newindex[j]];
				minind = j;
			}
		swap_int(newindex + minind, newindex + i);
	}
}
void podschetom(ULONGLONG*filesize, int n, int*newindex)//сортировка подсчетом
{
	ULONGLONG delta = 0, min = filesize[0], max = filesize[0];
	int *count;
	int i, j, _i_delta = 0, idx = 0;
	for (i = 1; i < n; i++)
	{
		if (filesize[i] < min)
			min = filesize[i];
		if (filesize[i] > max)
			max = filesize[i];
	}
	delta = max - min + 1;
	if (delta * (ULONGLONG)sizeof(int) > (ULONGLONG)UINT_MAX)
		return 1;
	/*    если будет выполнено условие выше, то delta не выйдет за границы    *
	* диапазона значений int, поэтому потеря данных при приведении исключена */
	_i_delta = (int)delta;
	count = (int*)malloc(_i_delta * sizeof(int));
	for (i = 0; i < _i_delta; i++)
		count[i] = 0;
	for (i = 0; i < n; i++)
		count[filesize[i] - min]++;
	for (i = 0; i < _i_delta; i++)
		for (j = 0; j < count[i]; j++, idx++)
			newindex[idx] = find_by_size(i + min, j + 1, filesize, n);
	free(count);
	return 0;
}
void quicksort(ULONGLONG *filesize, int *newindex, int n1, int n2)//быстрая сортировка
{
	ULONGLONG comp = filesize[(n1 + n2) / 2];
	int i = n1, j = n2;
	do {
		while (filesize[i] < comp)
			i++;
		while (filesize[j] > comp)
			j--;
		if (i <= j) {
			if (filesize[i] > filesize[j])
			{
				swap_int(newindex + i, newindex + j);
				swap_ULL(filesize + i, filesize + j);
			}
			i++;
			j--;
		}
	} while (i <= j);
	if (i < n2)
		quicksort(filesize, newindex, i, n2);
	if (j > n1)
		quicksort(filesize, newindex, n1, j);
}
void quicksort_start(ULONGLONG *filesize, int n1, int n2, int* newindex)//дополнение к быстрой сортировке
{
	int i, total_length = n2 - n1 + 1;
	ULONGLONG *newSizes;
	newSizes = (ULONGLONG*)malloc(total_length * sizeof(ULONGLONG));
	for (i = 0; i < total_length; i++)
		newSizes[i] = filesize[i + n1];
	quicksort(newSizes, newindex, n1, n2);
	free(newSizes);
}
void print(ULONGLONG* filesize, wchar_t **fileNames, int kolvo)//печать
{
	int i;
	for (i = 0; i < kolvo; i++)
	{
		wprintf(L"file  %s размер %lld \n", fileNames[i], filesize[i]);
	}
}
void menu()//
{
	printf("Меню программы!\n");
	printf("Введите 1 для сортировки пузырьком!\n");
	printf("Введите 2 для сортировки вставкой!\n");
	printf("Введите 3 для сортировки выбором!\n");
	printf("Введите 4 для сортировки подсчетом!\n");//+
	printf("Введите 5 для быстрой сортировки(сортировки Хоара)!\n");
	printf("Введите 6 для сортировки слиянием!\n");
	printf("Вы выбрали сортировку номер: ");
}
void main()
{
	int i = 0;
	double total_time;
	char e;
	int choice, flag = 1;
	clock_t start, end;
	wchar_t **fileNames;
	wchar_t* ca;
	int*filesindex;
	char*a;
	ULONGLONG*filesize;
	ULONGLONG*filesizemain;
	int*newindex;
	setlocale(LC_ALL, "Russian");
	printf("Файловый менеджер!\n");
	while (flag = 1)
	{
		printf("Введите путь!\n");
		fileNames = (wchar_t**)malloc(ROFL * sizeof(wchar_t*));
		filesindex = (int*)malloc((kolvo + 1) * sizeof(int));
		newindex = (int*)malloc(kolvo * sizeof(int));
		filesizemain = (ULONGLONG*)malloc(MAX_FILES * sizeof(ULONGLONG));
		filesize = (ULONGLONG*)malloc(MAX_FILES * sizeof(ULONGLONG));
		a = (char*)malloc(MAX_LEN);
		ca = (wchar_t*)malloc(MAX_LEN);
		fgets(a, MAX_LEN, stdin);
		a[strlen(a) - 1] = '\0';
		swprintf(ca, MAX_LEN, L"%hs", a);
		ListDirectoryContents(ca, filesize, fileNames);
		if (kolvo > 0)
		{
			print(filesize, fileNames, kolvo);
			flag = 1;
			for (i = 0; i < kolvo; i++)
			{
				filesindex[i] = i;
				newindex[i] = i;
			}
			menu();
			scanf("%d", &choice);
			switch (choice)
			{
			case 1:
				scanf("%c", &e);
				anihilation(filesizemain, filesize, filesindex, newindex, kolvo);
				printf("Сортировка пузырьком!\n");
				start = clock();
				bubble(filesize, newindex, kolvo);
				end = clock();
				for (i = 0; i < kolvo; i++)
				{
					wprintf(L"file %s размер %lld \n", fileNames[newindex[i]], filesize[newindex[i]]);
				}
				total_time = (double)(end - start) / CLOCKS_PER_SEC;
				printf("Время сортировки: %.3lf с\n", total_time);
				break;
			case 2:
				scanf("%c", &e);
				anihilation(filesizemain, filesize, filesindex, newindex, kolvo);
				printf("Сортировка вставкой\n");
				start = clock();
				insert(filesize, newindex, kolvo);
				end = clock();
				for (i = 0; i < kolvo; i++)
				{
					wprintf(L"file %s размер %lld \n", fileNames[newindex[i]], filesize[newindex[i]]);
				}
				total_time = (double)(end - start) / CLOCKS_PER_SEC;
				printf("Время сортировки: %.3lf с\n", total_time);
				break;
			case 3:
				scanf("%c", &e);
				anihilation(filesizemain, filesize, filesindex, newindex, kolvo);
				printf("Сортировка выбором\n");
				start = clock();
				choose(filesize, kolvo, newindex);
				end = clock();
				for (i = 0; i < kolvo; i++)
				{
					wprintf(L"file %s размер %lld \n", fileNames[newindex[i]], filesize[newindex[i]]);
				}
				total_time = (double)(end - start) / CLOCKS_PER_SEC;
				printf("Время сортировки: %.3lf с\n", total_time);
				break;
			case 4:
				scanf("%c", &e);
				anihilation(filesizemain, filesize, filesindex, newindex, kolvo);
				printf("Сортировка подсчетом!");
				start = clock();
				podschetom(filesize, kolvo, newindex);
				end = clock();
				for (i = 0; i < kolvo; i++)
				{
					wprintf(L"file %s размер %lld \n", fileNames[newindex[i]], filesize[newindex[i]]);
				}
				total_time = (double)(end - start) / CLOCKS_PER_SEC;
				printf("Время сортировки: %.3lf с\n", total_time);
				break;
			case 5:
				scanf("%c", &e);
				anihilation(filesizemain, filesize, filesindex, newindex, kolvo);
				printf("Быстрая сортировка\n");
				start = clock();
				quicksort_start(filesize, 0, kolvo - 1, newindex);
				end = clock();
				for (i = 0; i < kolvo; i++)
				{
					wprintf(L"file %s размер %lld \n", fileNames[newindex[i]], filesize[newindex[i]]);
				}
				total_time = (double)(end - start) / CLOCKS_PER_SEC;
				printf("Время сортировки: %.3lf с\n", total_time);
				break;
			case 6:
				scanf("%c", &e);
				anihilation(filesizemain, filesize, filesindex, newindex, kolvo);
				printf("Сортировка слиянием\n");
				start = clock();
				MergeSort(newindex, filesize, 0, (kolvo - 1));
				end = clock();
				for (i = 0; i < kolvo; i++)
				{
					wprintf(L"file %s размер %lld \n", fileNames[newindex[i]], filesize[newindex[i]]);
				}
				total_time = (double)(end - start) / CLOCKS_PER_SEC;
				printf("Время сортировки: %.3lf с\n", total_time);
				break;
			default:
				menu();
				scanf("%d", &choice);
			}
			kolvo = 0;
		}
	}
	system("pause");
}