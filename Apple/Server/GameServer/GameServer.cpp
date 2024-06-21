#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>

vector<int32> v;

void Push()
{
	for(int32 i=0; i<1000; ++i)
	{
		v.push_back(1);
	}
}



int main()
{
	v.reserve(20000);

	thread t1(Push);
	thread t2(Push);

	t1.join();
	t2.join();

	int32 sum{ 0 };
	for (auto i : v)
	{
		sum += i;
	}

	cout << sum << endl;

	return 0;
}
