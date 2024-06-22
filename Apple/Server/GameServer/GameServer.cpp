#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>

int32 sum = 0;
mutex m;

void Add()
{
	for(int32 i=0; i< 10000; ++i)
	{
		lock_guard<mutex> guard(m);
		sum++;
	}
}

void Sub()
{
	for (int32 i = 0; i < 10000; ++i)
	{
		lock_guard<mutex> guard(m);
		sum--;
	}
}


int main()
{
	std::thread t1(Add);
	std::thread t2(Sub);

	t1.join();
	t2.join();


	cout << sum << endl;


	return 0;
}
