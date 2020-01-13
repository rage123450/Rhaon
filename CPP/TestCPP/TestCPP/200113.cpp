#include <iostream>
#include <memory>
using namespace std;

class Heap
{
private:
	int data[10] = { 0, };
	int size = 0;

public:
	Heap() {}
	~Heap() {}

public:
	void Swap(int& a,int &b)
	{
		int temp = a;
		a = b;
		b = a;
	}

	void Push(int n)
	{
	}

	int Pop()
	{
	}
};

int main()
{
	unique_ptr<Heap> heap = make_unique<Heap>();

	heap->Push(1);
	heap->Push(2);
	heap->Push(3);
	heap->Push(4);
	heap->Push(5);
	heap->Push(6);
	heap->Push(7);

	heap->Pop();
	heap->Pop();
	heap->Pop();

	return 0;
}