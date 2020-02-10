#include "std.h"

int main()
{
	list<int> temp;
	temp.push_back(1);
	temp.push_back(1);
	temp.push_back(1);
	temp.push_back(1);
	temp.push_back(1);
	temp.push_back(1);

	for(auto& i : temp)
	{
		cout << i << endl;
	}
	temp.unique();
	cout << "=========================" << endl;
	for(auto& i : temp)
	{
		cout << i << endl;
	}


	return 0;
}