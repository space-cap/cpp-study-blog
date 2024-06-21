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
		v.push_back(i);
	}
}



int main()
{
	thread t1(Push);
	thread t2(Push);

	t1.join();
	t2.join();


    


    return 0;
}
