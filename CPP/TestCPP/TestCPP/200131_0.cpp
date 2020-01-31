#include "std.h"

void Test(int(&t)[3])
{
	for(auto& i : t)
	{
		cout << i << endl;
	}
}

int main()
{
	Test({ 1,2,3 });


	//vector<int> vec;
	//vec.emplace_back(1);

	//vector<int> vec2 = {2,3,4};

	//vec.insert(vec.begin()+vec.size(), vec2.begin(), vec2.end());

	//for(auto& i : vec)
	//{
	//	cout << i << endl;
	//}

	//vec.clear();
	//cout << vec.capacity() << endl;

	return 0;
}