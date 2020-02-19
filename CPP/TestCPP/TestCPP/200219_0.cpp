#include "std.h"

class Test
{
public:
	int n = 0;

public:
	Test() { cout << "constructor" << endl; }
	Test(const Test& ref) { cout << "copy constructor" << endl; }
	~Test() { cout << "desructor" << endl; };
};

int main()
{
	list<shared_ptr<Test>> test;

	test.emplace_back(make_shared<Test>());
	test.emplace_back(make_shared<Test>());
	test.emplace_back(make_shared<Test>());
	test.emplace_back(make_shared<Test>());
	test.emplace_back(make_shared<Test>());

	test.clear();


	return 0;
}