#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#define N 10
#define wordlength 10
void main()
{
	setlocale(LC_ALL, "Russian");
	srand((unsigned int)time(0));
	int f = 0, mode, code, i, j, a = 0;
	char name[N][wordlength] = { "milk" , "bread" , "juice" , "apple" , "butter" , "water" , "salt" , "meet" , "banana" , "chocolate" };
	int cost[N] = { 50, 30, 70, 15, 45, 10, 20, 500, 100, 90 };
	int discount[N];
	int kolvo[N] = { 0 };
	for (j = 0; j < N; j++)
		discount[j] = rand() * (1 - 50) / RAND_MAX + 50;
	do
	{
		printf("�������� ����� ������:\n");
		printf("������� 1, ����� ����������� ��������� �����\n");
		printf("������� 2, ����� ������� �������� ���������������� ������\n");
		printf("������� 3, ����� �������� ������ � ������ � ���\n");
		printf("������� 4, ����� ������������ ��� �� �������\n");
		printf("������� 5, ����� ���������� �������� ����� � ������\n");
		scanf("%d", &mode);
		switch (mode)
		{
		case 1:
		{
			printf("������� �����-��� ������(1-10)\n");
			do
				scanf("%d", &code);
			while ((code < 1) || (code > 10));
			break;
		}
		case 2:
		{
			printf("�����-���:""%d\n", code);
			for (i = 0; i < wordlength; i++)
				printf("%c", name[code - 1][i]);
			printf("����(���.):""%d\n", cost[code - 1]);
			printf("������(����.):""%d\n", discount[code - 1]);
			break;
		}
		case 3:
		{
			printf("����� �������� � ���!\n");
			kolvo[code - 1]++;
			break;
		}
		case 4:
		{
			for (j = 0; j < N; j++)
			{
				if (kolvo[j] != 0)
				{
					for (i = 0; i < wordlength; i++)
						printf("%c", name[j][i]);
					printf("�����������:""%d", kolvo[j]);
					printf("����:""%d", cost[j]);
					printf("����� ���������:""%d", kolvo[j] * cost[j]);
					a += (cost[j] - (cost[j] * discount[j] / 100))*kolvo[j];
				}
			}
			break;
		}
		case 5:
		{
			printf("�������� ����� � ������ � ������ ������:");
			printf("%d", a);
		}
		}
	} while (mode != 5);
	system("pause");
}