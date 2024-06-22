﻿#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>


class SpinLock
{
public:
	void lock()
	{
		// CAS ( Compare-And-Swap)
		bool expected = false;
		bool desired = true;

		while(_locked.compare_exchange_strong(expected, desired) == false)
		{
			expected = false;

			//this_thread::sleep_for(chrono::milliseconds(100));
			this_thread::sleep_for(0ms);
			// this_thread::yield(); // 
		}
	}

	void unlock()
	{
		//_locked = false;
		_locked.store(false);
	}

private:
	atomic<bool> _locked = false;
};


int32 sum = 0;
mutex m;
SpinLock spinLock;

void Add()
{
	for(int32 i=0; i< 10000; ++i)
	{
		lock_guard<SpinLock> guard(spinLock);
		sum++;
	}
}

void Sub()
{
	for (int32 i = 0; i < 10000; ++i)
	{
		lock_guard<SpinLock> guard(spinLock);
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
