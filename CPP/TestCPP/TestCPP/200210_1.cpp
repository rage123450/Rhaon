#include "std.h"

class Visitor;
class Element
{
public:
	virtual void accept(Visitor* v) abstract;
};

class ElementA : public Element
{
	// Element��(��) ���� ��ӵ�
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
	// Visitor��(��) ���� ��ӵ�
	virtual void visit(Element * e) override
	{
		// e�� ������ ó���ϴ� �ڵ�
	}
};

int main()
{
	return 0;
}