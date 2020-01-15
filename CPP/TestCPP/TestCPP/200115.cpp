#include <iostream>
#include <vector>
#include <functional>
#include <memory>

using namespace std;
using namespace std::placeholders;

void Test(vector<int> vec)
{
	for(auto& i : vec)
	{
		cout << i << endl;
	}
}

void Test2(vector<function<void(void)>> vec)
{
	for(auto& i : vec)
	{
		i();
	}
}

void Hi()
{
}

int multiply(int a, int b)
{
	return a * b;
}

class A;
class H
{
public:
	int n = 22;

public:
	H(shared_ptr<A> _a) 
	{
		a = _a;
	}

public:
	shared_ptr<A> a;
};

class A
{
public:
	int n = 10;
};

auto main()->int
{
	shared_ptr<A> a = make_shared<A>();
	cout << a->n << endl;

	shared_ptr<H> h = make_shared<H>(a);
	h->a->n += 100;
	h->a->n += 1000;
	cout << a->n << endl;

	return 0;
}