#include "std.h"

class A
{
public:
	A() { /*cout << "A Ctor" << endl;*/ }
	virtual ~A() {/* cout << "A Dtor" << endl;*/ }
};

class AA : public A
{
public:
	AA() { /*cout << "AA Ctor" << endl;*/ }
	virtual ~AA() { /*cout << "AA Dtor" << endl;*/ }

public:
	void Print() { cout << "Hi~" << endl; }
};

auto main()->int
{
	vector<shared_ptr<A>> vec;

	vec.emplace_back(make_shared<AA>());
	vec.emplace_back(make_shared<AA>());
	vec.emplace_back(make_shared<AA>());

	for(auto& i : vec)
	{
		dynamic_cast<AA*>(i.get())->Print();
	}

	return 0;
}