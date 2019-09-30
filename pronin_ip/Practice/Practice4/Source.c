#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define N 10
#define wordlength 10
void main()
{
	setlocale(LC_ALL, "Russian");
	srand((unsigned int)time(0));
	int f = 0, mode, code, i, j, a = 0, flag = 0, index = 0;
	char name[N][wordlength] = { "milk" , "bread" , "juice" , "apple" , "butter" , "water" , "salt" , "meet" , "banana" , "chocolate" }; ////////////
	char producycode[N][4] = { "0001", "1204", "3405", "1245", "7634", "4593", "9812", "3498", "9875", "1221" };
	int cost[N] = { 50, 30, 70, 15, 45, 10, 20, 500, 100, 90 };
	int discount[N];
	int kolvo[N] = { 0 };
	char stroka[4];
	for (j = 0; j < N; j++)
		discount[j] = rand() * (1 - 50) / RAND_MAX + 50;
	do
	{
		printf("Выберите режим работы:\n");
		printf("Введите 1, чтобы сканировать очередной товар\n");
		printf("Введите 2, чтобы вывести описание отсканированного товара\n");
		printf("Введите 3, чтобы добавить данные о товаре в чек\n");
		printf("Введите 4, чтобы сформировать чек за покупку\n");
		printf("Введите 5, чтобы рассчитать итоговую сумму к опалте\n");
		scanf("%d", &mode);
		switch (mode)
		{
		case 1:
		{
			printf("Введиет штрих-код товара(0001, 1204, 3405, 1245, 7634, 4593, 9812, 3498, 9875, 1221)\n");
			//do
				//scanf("%d", &code);
				gets(stroka);
			//while ((code < 0) || (code > 9999));
			//break;
		}
		case 2:
		{
			for (i = 0; i < 10; i++)
				if (strcmp(stroka, name[i] == 0))
				{
					//printf("штрих-код:""%d\n", code);
					printf("штрих код:\n");
					puts(stroka);
					//for (j = 0; j < wordlength; j++)
						//printf("%c", name[i][j]);
					printf("%s", name[i]);
					printf("цена(руб.):""%d\n", cost[i]);
					printf("скидка(проц.):""%d\n", discount[i]);
					flag = 1;
					index = i;
				}
			if (flag = 0)
			break;
		}
		case 3:
		{
			printf("товар добавлен в чек!\n");
			kolvo[index]++;
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
					printf("колличестов:""%d", kolvo[j]);
					printf("цена:""%d", cost[j]);
					printf("общая стоимость:""%d", kolvo[j] * cost[j]);
					a += (cost[j] - (cost[j] * discount[j] / 100))*kolvo[j];
				}
			}
			break;
		}
		case 5:
		{
			printf("итоговая сумма к оплате с учетом скидок:");
			printf("%d", a);
		}
		}
	} while (mode != 5);
	system("pause");
}