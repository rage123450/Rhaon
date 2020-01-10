#include "stdafx.h"
//
#include "MainGUI.h"

int main()
{
	//shared_ptr<CMainGUI> pMainGUI = make_shared<CMainGUI>();

	map<int,int> a = { 1,2,3,4,5 };
	vector<int> b = { 1,2,3};

	copy(begin(a), end(a), begin(b));

	for_each(begin(b), end(b), [&](int x) {cout << x << endl; });

	return 0;
}

