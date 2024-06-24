#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>




int main()
{
	atomic<bool> flag = false;
	//flag.is_lock_free();

	//flag = true;
	flag.store(true);

	//bool val = flag;
	bool val = flag.load(memory_order_seq_cst);


	{
		bool prev = flag.exchange(true);
		//bool prev = flag;
		//flag = true;


	}

	// CAS (Compare-And-Swap) 조건부 수정
	{
		bool expected = false;
		bool desired = true;
		flag.compare_exchange_strong(expected, desired);

		if(flag == expected)
		{
			flag = desired;
			return true;
		}
		else
		{
			expected = flag;
			return false;
		}
	}


	return 0;
}


