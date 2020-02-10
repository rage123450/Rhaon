#include "std.h"

class Visitor;
class Element
{
public:
	virtual void accept(Visitor* v) abstract;
};

class ElementA : public Element
{
	// Element을(를) 통해 상속됨
	virtual void accept(Visitor * v) override
	{
		v->visit(this);
	}
};

class Visitor
{
public:
	virtual void visit(Element* e) abstract;
};

class VisitorElementA : public Visitor
{
public:
	// Visitor을(를) 통해 상속됨
	virtual void visit(Element * e) override
	{
		// e를 가지고 처리하는 코드
	}
};

int main()
{
	return 0;
}