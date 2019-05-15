#include "container.h"
#include "container+.h"
void main()
{
	int a[] = { 1, 2, 3, 4, 5 };
	float b[] = { 1.1f, 2.22f, 3.03f, 4.f, -5.5f };
	cout << "Container 1:" << endl;
	Container <int, 6> container_1(5, a);
	cout << container_1 << endl;
	container_1.Add(2);
	container_1.Add(6);
	cout << container_1.IsFull() << endl;
	cout << container_1.IsEmpty() << endl;
	container_1.Add(7);
	container_1.Delete(1);
	cout << container_1 << endl;

	cout << endl;

	cout << "Container 2:" << endl;
	Container <float, 7> container_2(5, b);
	cout << container_2 << endl;
	container_2.Add(2.22f);
	container_2.Add(6.666f);
	cout << container_2.IsFull() << endl;
	cout << container_2.IsEmpty() << endl;
	container_2.Add(-7.07f);
	container_2.Delete(1.1f);
	cout << container_2 << endl;

	int* a1[5];
	float* b1[5];
	for (int i = 0; i < 5; i++)
	{
		a1[i] = &a[i];
		b1[i] = &b[i];
	}
	cout << endl;

	cout << "Container 3:" << endl;
	Container <int*, 6> container_3(5, a1);
	cout << container_3 << endl;
	int elem = 2;
	int elem1 = 6;
	int elem2 = 7;
	int elem3 = 1;
	int *p = &elem;
	int *p1 = &elem1;
	int *p2 = &elem2;
	int *p3 = &elem3;
	container_3.Add(p);
	container_3.Add(p1);
	cout << container_3.IsFull() << endl;
	cout << container_3.IsEmpty() << endl;
	container_3.Add(p2);
	container_3.Delete(p3);
	cout << container_3 << endl;

	cout << endl;

	cout << "Container 4:" << endl;
	Container <float*, 7> container_4(5, b1);
	cout << container_4 << endl;
	float elem_ = 2;
	float elem1_ = 6;
	float elem2_ = 7;
	float elem3_ = 1;
	float *p_ = &elem_;
	float *p1_ = &elem1_;
	float *p2_ = &elem2_;
	float *p3_ = &elem3_;
	container_4.Add(p_);
	container_4.Add(p1_);
	cout << container_4.IsFull() << endl;
	cout << container_4.IsEmpty() << endl;
	container_4.Add(p2_);
	container_4.Delete(p3_);
	cout << container_4 << endl;

	system("pause");
}