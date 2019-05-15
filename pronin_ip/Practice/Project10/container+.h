#include "container.h"
template <typename T, int maxsize>
class Container <T*, maxsize>
{
private:
	T** arr;
	int count;
	const static int sizestap = 10;
public:
	Container(int, T**);
	Container();
	Container(const Container &);
	~Container();
	bool IsFull() const;
	bool IsEmpty() const;
	int Find(T*) const;
	void Add(T*);
	void Deletebyidx(int);
	void Delete(T*);
	void AddSize(int);
	T& operator[](int);
	const T& operator[](int) const;
	friend ostream& operator<<(ostream& o, const Container& container)
	{
		for (int i = 0; i < container.count; i++)
			o << container.arr[i] << " ";
		return o;
	}
};



template <typename T, int maxsize>
Container <T*, maxsize> ::Container()
{
	cout = 5;
	arr = new T*[maxsize];
}
template <typename T, int maxsize>
Container <T*, maxsize> ::Container(int a, T** b)
{
	count = a;
	arr = new T*[maxsize];
	for (int i = 0; i < count; i++)
		arr[i] = new T(*(b[i]));
}
template <typename T, int maxsize>
Container <T*, maxsize> ::Container(const Container <T*, maxsize> &a)
{
	count = a.count;
	arr = new T*[count];
	for (int i = 0; i < count; i++)
		arr[i] = new T(*(a.arr[i]));
}
template <typename T, int maxsize>
Container <T*, maxsize> ::~Container()
{
	count = 0;
	for (int i = 0; i < count; i++)
		delete arr[i];
	delete[] arr;
	arr = NULL;
}
template <typename T, int maxsize>
bool Container <T*, maxsize>::IsFull() const
{
	return (count == maxsize);
}
template <typename T, int maxsize>
bool Container <T*, maxsize>::IsEmpty() const
{
	return (count == 0);
}
template <typename T, int maxsize>
int Container <T*, maxsize>::Find(T* a) const
{
	int flag = -1;
	for (int i = 0; i < count; i++)
		if (*arr[i] == *a)
			flag = i;
	return flag;
}
template <typename T, int maxsize>
void Container <T*, maxsize>::Add(T* a)
{
	if (Find(a) == -1)
	{
		if (count == maxsize)
		{
			AddSize(0);
			cout << "maxsize was increased" << endl;
		}
		arr[count] = a;
		count++;
		cout << "element" << " " << a << " " << "was added successfully" << endl;
	}
	else
		cout << "element" << " " << a << " " << "already exists" << endl;
}
template <typename T, int maxsize>
void Container <T*, maxsize>::Deletebyidx(int idx)
{
	arr[idx] = arr[count - 1];
	count--;
}
template <typename T, int maxsize>
void Container <T*, maxsize>::Delete(T* a)
{
	Deletebyidx(Find(a));
	cout << "element" << " " << a << " " << "was deleted successfully" << endl;
}
template <typename T, int maxsize>
void Container <T*, maxsize>::AddSize(int a)
{
	if (a == 0) a = sizestap;
	int max = maxsize;
	max += a;
	T **tmp = new T*[max];
	for (int i = 0; i < count; i++)
		tmp[i] = new T(*(arr[i]));
	arr = tmp;
}
template <typename T, int maxsize>
T& Container <T*, maxsize>::operator[](int a)
{
	return *arr[a];
}
template <typename T, int maxsize>
const T& Container <T*, maxsize>::operator[](int a) const
{
	return *arr[a];
}

