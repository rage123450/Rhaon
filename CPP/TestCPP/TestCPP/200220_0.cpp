#include "main.h"
template<int x, int n>
struct Power { enum { value = x * Power<x, n - 1>::value }; };

template<int x>
struct Power<x, 0> { enum { value = 1 }; };

template<int n>
struct Factorial { enum { value = n * Factorial<n - 1>::value }; };

template<>
struct Factorial<0> { enum { value = 1 }; };

int main()
{
	cout << Power<2, 0>::value << endl;
	cout << Factorial<10>::value << endl;
	return 0;
}