#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <locale.h>

void main()
{
	float x, y, r, x1, y1, r1, L;
	setlocale(LC_ALL, "Russian");
	printf("������� ���������� ������ ������ ����������");
	scanf("%f %f", &x, &y);
	printf("������� ������ ������ ����������");
	scanf("%f", &r);
	printf("������� ���������� ������ ������ ����������");
	scanf("%f %f", &x1, &y1);
	printf("������� ������ ������ ����������");
	scanf("%f", &r1);
	L = sqrt((x - x1)*(x - x1) + (y - y1)*(y - y1));
	if ((r < 0) || (r1 < 0))
	{
		printf("������");
		return;
	}
	if (L > (r + r1))
	{
		printf("���������� �� ������������");
		return;
	}
	if (L == (r + r1))
	{
		printf("���������� �������� ������");
		return;
	}
	if ((x == x1) && (y == y1) && (r == r1))
	{
		printf("���������� ���������");
		return;
	}
	if (((r > r1) && (L == r - r1)) || ((r1 > r) && (L == r1 - r)))
	{
		printf("���������� ����� ��������");
		return;
	}
	if ((r > r1) && (L < (r - r1)))
	{
		printf("���������� ��� ������ � ���������� ����");
		return;
	}
	if ((r1 > r) && (L < (r1 - r)))
	{
		printf("���������� ���� ������ � ���������� ���");
		return;
	}
	printf("���������� ������������");
	system("pause");
}