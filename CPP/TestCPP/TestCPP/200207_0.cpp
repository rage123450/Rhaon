#include "std.h"

class Breed
{
private:
	int m_nHealth;
	const char* m_cAttack;

public:
	Breed(int _nHealth, const char* _cAttack) : m_nHealth(_nHealth), m_cAttack(_cAttack) {}
	~Breed() {}

public:
	int GetHealth() { return m_nHealth; }
	const char* GetAttack() { return m_cAttack; }
};

class Monster
{
private:
	int m_nHealth;
	Breed& m_Breed;

public:
	Monster(Breed& _Breed) :m_nHealth(_Breed.GetHealth()), m_Breed(_Breed) {}
	~Monster() {}

public:
	const char* GetAttack() { return m_Breed.GetAttack(); }
};

int main()
{
	return 0;
}