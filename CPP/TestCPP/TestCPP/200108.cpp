#include <iostream>
#include <string>
#include <array>
#include <random>
#include <bitset>
#include <time.h>
using namespace std;

random_device rd;
mt19937_64 rng(rd());

enum ESRP
{
	SRP_SCISSORS,
	SRP_ROCK,
	SRP_PAPER,
	SRP_END
};

constexpr int MAX = 1000000;


uniform_int_distribution<__int64> r(ESRP::SRP_ROCK, ESRP::SRP_END - 1);
string strText = "";


string GetSelect(int _nSelect)
{
	switch(_nSelect)
	{
	case SRP_SCISSORS:
		return "가위";
	case SRP_ROCK:
		return "바위";
	case SRP_PAPER:
		return "보";
	}

	return "???";
}

int Sum(int a, int b)
{
	return a != 0 && b != 0 ? Sum(a^b, (a&b) << 1) : a == 0 ? a : b;

	if(a == 0)
	{
		return b;
	}
	else if(b == 0)
	{
		return a;
	}

	int s = a ^ b;
	int c = (a&b) << 1;

	return Sum(s, c);
}


void TestSwitch()
{
	clock_t start, end;
	double result;

	start = clock();

	for(int i = 0; i < MAX; i++)
	{
		int me = r(rng);
		int com = r(rng);

		cout << "Me : " << GetSelect(me) << " vs ";
		cout << "Com : " << GetSelect(com) << " ====> ";

		switch(me)
		{
		case SRP_SCISSORS:
			switch(com)
			{
			case SRP_SCISSORS:
				cout << "Draw" << endl;
				break;

			case SRP_ROCK:
				cout << "Lose" << endl;
				break;

			case SRP_PAPER:
				cout << "Win" << endl;
				break;
			}
			break;

		case SRP_ROCK:
			switch(com)
			{
			case SRP_SCISSORS:
				cout << "Win" << endl;
				break;

			case SRP_ROCK:
				cout << "Draw" << endl;
				break;

			case SRP_PAPER:
				cout << "Lose" << endl;

				break;
			}
			break;

		case SRP_PAPER:
			switch(com)
			{
			case SRP_SCISSORS:
				cout << "Lose" << endl;
				break;

			case SRP_ROCK:
				cout << "Win" << endl;
				break;

			case SRP_PAPER:
				cout << "Draw" << endl;
				break;
			}
			break;
		}
	}

	end = clock();

	printf("Switch : %f", (double)(end - start));
}

void TestMy()
{
	clock_t start, end;
	double result;

	start = clock();

	for(int i = 0; i < MAX; i++)
	{
		int me = r(rng);
		int com = r(rng);

		cout << "Me : " << GetSelect(me) << " vs ";
		cout << "Com : " << GetSelect(com) << " ====> ";

		strText = (me - com & 0) ? "Draw" : (me + SRP_END - 1) % SRP_END == com ? "Win" : "Lose";
		cout << strText << endl;
	}

	end = clock();

	printf("If : %f", (double)(end - start));
}

int main()
{
	//TestSwitch();
	
	TestMy();

	return 0;
}

