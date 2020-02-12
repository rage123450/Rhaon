#include "std.h"

int gcd(int n, int m)
{
	if(m == 0)
	{
		return n;
	}
	return gcd(m, n % m);
}

int foo(int n)
{
	if(n == 0)
	{
		return 1;
	}

	return 2 * foo(n - 1);
}

int foo_tail(int n, int temp)
{
	if(n == 1)
	{
		return temp;
	}

	return foo_tail(n - 1, 2 * temp);
}

int foo2(int n)
{
	return foo_tail(n, 2);
}

int main()
{
	//cout << gcd(582, 129) << endl;
	cout << foo2(10) << endl;
	return 0;
}