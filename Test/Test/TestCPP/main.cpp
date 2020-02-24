#include "main.h"

void Test(reference_wrapper<vector<int>> _vec)
{
	for(auto& i : _vec.get())
	{
		cout << i << endl;
	}
}

int main()
{
	vector<int> vec = { 1,2,3,4 };
	Test(ref(vec));

	return 0;
}