#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>
void main()
{
	setlocale(LC_ALL, "Russian");
	int a, b, c, x, y, z, w;
	char q;
	c = 0;
	z = 0;
	x = 0;
	y = 1000;
	srand((unsigned int)time(0));

	printf("������� 1, ���� ������ �������� ����; ������� 2, ���� ������ �������� �����");
	scanf("%d", &w);
	if (w == 1)
	{
		do { a = rand(); } while ((a < 0) || (a > 1000));

		printf("��������� �����");
		do {
			scanf("%d", &b);
			if (b > a) printf("���������� ����� ������");
			if (b < a) printf("���������� ����� ������");
			c += 1;
		} while (b != a);
		printf("����� �������:""%d", c);
	}
	if (w == 2)
	{
		printf("��������� �����");
		scanf("%d", &a);
		do {
			do { b = rand(); } while ((b < x) || (b > y));
			printf("%d", b);
			printf("������� <, ���� ���� ����� ������; ������� >, ���� ���� ����� ������");
			scanf("%*c%c", &q);
			if (q == '<' ) 
			y = b; 
			else 
			{
			if (q == '>') 
			x = b; 
			else  
			return;
			}
			z += 1;
		} while (b != a);
		printf("����� �������:""%d", z);
	}
}