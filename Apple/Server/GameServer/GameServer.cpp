#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>


int64 Calculate()
{
	int64 sum = 0;

	for (int32 i = 0; i < 100; ++i)
	{
		sum += i;
	}

	return sum;
}

int main()
{
	int64 sum = Calculate();
	cout << sum << endl;

	thread t(Calculate);

	// todo


	t.join();

	return 0;
}
