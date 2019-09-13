#include "Header.h"
#include <stdio.h>
void main()
{
	int x;
	double y, z, t;
	Vector a, b, c, d;
	a = Input(3);
	b = Input(3);
	printf("vector a:");
	Output(a);
	printf("\n");
	printf("vector b:");
	Output(b);
	printf("\n");

	c = Sum(a, b);
	printf("sum:");
	Output(c);
	printf("\n");

	d = Raz(a, b);
	printf("raz:");
	Output(d);
	printf("\n");

	x = Scayler(a, b);
	printf("scayler:");
	printf("%d\n", x);

	y = Length(a);
	printf("dlina vectora a:");
	printf("%.3f\n", y);
	z = Length(b);
	printf("dlina vectora b:");
	printf("%.3f\n", z);

	t = Corner(a, b);
	printf("corner v rad.:");
	printf("%.3f", t);

	Delete(a);
	Delete(b);
	Delete(c);
	Delete(d);
	system("pause");
}