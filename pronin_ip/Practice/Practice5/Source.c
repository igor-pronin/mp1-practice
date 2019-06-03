﻿#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_LEN 2048
#define K 100000
typedef struct
{
	wchar_t Name[2048];
	ULONGLONG Size;
}namesize;

void insert(namesize a[], int n)
{
	int i, j, tmp;
	namesize stmp;
	for (i = 1; i < n; i++)
	{
		j = i - 1;
		tmp = a[i].Size;
		stmp = a[i];
		while ((j >= 0) && (a[j].Size > tmp))
		{
			a[j + 1] = a[j];
			a[j] = stmp;
			j--;
		}
	}
}

void bubblesort(namesize a[], int n)
{
	int i, j;
	namesize tmp;
	for (i = 0; i < n; i++)
	{
		for (j = 1; j < n - i; j++)
		{
			if (a[j - 1].Size > a[j].Size)
			{
				tmp = a[j];
				a[j] = a[j - 1];
				a[j - 1] = tmp;
			}
		}
	}
}


void choose(namesize a[], int n)
{
	int i, j, minidx;
	namesize stmp;
	for (i = 0; i < n; i++)
	{
		minidx = i;
		for (j = i + 1; j < n; j++)
			if (a[j].Size < a[minidx].Size)
			{
				minidx = j;
			}
		stmp = a[i];
		a[i] = a[minidx];
		a[minidx] = stmp;
	}
}

void count(namesize a[], int n)
{
	int i, b = 0;
	int j;
	namesize* c = (namesize*)malloc(K * sizeof(namesize));
	for (i = 0; i < n; i++) c[a[i].Size] = a[i];
	for (j = 0; j < K; j++)
		if (a[j].Size == 0)
		{
			a[b] = c[j];
			b++;
		}
}

void quicksort(namesize a[], int n1, int n2)
{
	if (n1 < n2)
	{
		int left = n1, right = n2;
		ULONGLONG middle = a[(left + right) / 2].Size;
		do
		{
			while (a[left].Size < middle) left++;
			while (a[right].Size > middle) right--;
			if (left <= right)
			{
				namesize tmp = a[left];
				a[left] = a[right];
				a[right] = tmp;
				left++;
				right--;
			}
		} while (left <= right);
		quicksort(a, n1, right);
		quicksort(a, left, n2);
	}
}

void merge(namesize arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	namesize* L = (namesize*)malloc(n1 * sizeof(namesize));
	namesize* R = (namesize*)malloc(n2 * sizeof(namesize));
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i].Size <= R[j].Size)
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergesort(namesize arr[], int l, int r)
{
	if (l < r)
	{
		int m = l + (r - l) / 2;
		mergesort(arr, l, m);
		mergesort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}

int DirectorySize(const wchar_t *Dir)
{
	WIN32_FIND_DATA File;
	HANDLE Find = NULL;
	wchar_t Path[2048];
	int i = 0;
	wsprintf(Path, L"%s\\*.*", Dir);
	if ((Find = FindFirstFile(Path, &File)) == INVALID_HANDLE_VALUE)
	{
		return 0;
	}
	do
	{
		if (wcscmp(File.cFileName, L".") != 0 && wcscmp(File.cFileName, L"..") != 0)
		{
			i++;
		}
	} while (FindNextFile(Find, &File));
	FindClose(Find);
	return i;
}

int DirectoryRead(const wchar_t *Dir, namesize a[], int n)
{
	WIN32_FIND_DATA File;
	HANDLE Find = NULL;
	wchar_t Path[2048];
	int i = 0;
	wsprintf(Path, L"%s\\*.*", Dir);
	if ((Find = FindFirstFile(Path, &File)) == INVALID_HANDLE_VALUE)
	{
		wprintf(L"Path not found: [%s]\n", Dir);
		return 1;
	}
	do
	{
		if (wcscmp(File.cFileName, L".") != 0 && wcscmp(File.cFileName, L"..") != 0)
		{
			ULONGLONG fileSize = File.nFileSizeHigh;
			fileSize <<= sizeof(File.nFileSizeHigh) * 8;
			fileSize |= File.nFileSizeLow;
			namesize file;
			wsprintf(Path, L"%s\\%s", Dir, File.cFileName);
			wcsncpy_s(file.Name, 100, Path, 100);
			file.Size = fileSize;
			a[i] = file;
			i++;
		}
	} while (FindNextFile(Find, &File) && i < n);
	FindClose(Find);
	return 0;
}

void main()
{
	char* a;
	wchar_t* x;
	int flag = 1;
	int par, i, n;
	namesize* b;
	clock_t start, end;
	printf("Enter directory name:\n");
	a = (char*)malloc(MAX_LEN);
	x = (wchar_t*)malloc(MAX_LEN);
	fgets(a, MAX_LEN, stdin);
	a[strlen(a) - 1] = '\0';
	swprintf(x, MAX_LEN, L"%hs", a);
	n = DirectorySize(x);
	b = (namesize*)malloc(n * sizeof(namesize));
	printf("Hello");
	par = DirectoryRead(x, b, n);
	if (par == 1) return;

	while (1)
	{
		printf("Choose sorting method\n");
		printf("1. Bubble sort\n2. Choose sort\n3. Insert sort\n4. Count sort\n5. Quick sort\n6. Merge sort\n");
		scanf_s("%d", &par);
		switch (par)
		{
		case 1:
			start = clock();
			bubblesort(b, n);
			end = clock();
			for (i = 0; i < n; i++) wprintf(L"File: %ls Size: %lld\n", b[i].Name, b[i].Size);
			printf("Sort time: %.4lf\n", (double)(end - start) / CLOCKS_PER_SEC);
			break;
		case 2:
			start = clock();
			choose(b, n);
			end = clock();
			for (i = 0; i < n; i++) wprintf(L"File: %ls Size: %lld\n", b[i].Name, b[i].Size);
			printf("Sort time: %.4lf\n", (double)(end - start) / CLOCKS_PER_SEC);
			break;
		case 3:
			start = clock();
			insert(b, n);
			end = clock();
			for (i = 0; i < n; i++) wprintf(L"File: %ls Size: %lld\n", b[i].Name, b[i].Size);
			printf("Sort time: %.4lf\n", (double)(end - start) / CLOCKS_PER_SEC);
			break;
		case 4:
			start = clock();
			count(b, n);
			end = clock();
			for (i = 0; i < n; i++) wprintf(L"File: %ls Size: %lld\n", b[i].Name, b[i].Size);
			printf("Sort time: %.4lf\n", (double)(end - start) / CLOCKS_PER_SEC);
			break;
		case 5:
			start = clock();
			quicksort(b, 0, n - 1);
			end = clock();
			for (i = 0; i < n; i++) wprintf(L"File: %ls Size: %lld\n", b[i].Name, b[i].Size);
			printf("Sort time: %.4lf\n", (double)(end - start) / CLOCKS_PER_SEC);
			break;
		case 6:
			start = clock();
			mergesort(b, 0, n - 1);
			end = clock();
			for (i = 0; i < n; i++) wprintf(L"File: %ls Size: %lld\n", b[i].Name, b[i].Size);
			printf("Sort time: %.4lf\n", (double)(end - start) / CLOCKS_PER_SEC);
			break;
		default:
			printf("Invalid data entered\n");
			break;
		}
		printf("Enter 1 if you want to continue or 0 if you want to exit: ");
		scanf_s("%d", &flag);
		free(b);
		b = (namesize*)malloc(n * sizeof(namesize));
		DirectoryRead(x, b, n);
		if (flag == 0) return;
	}
	system("pause");
}
