#include "main.h"
union UTest
{
	int a;
	short b[2];
};


int main()
{
	UTest test;
	test.a = 1;

	cout << test.a << endl;
	cout << test.b << endl;

	return 0;
}