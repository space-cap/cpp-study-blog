#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>

//__declspec(thread) int value;
thread_local int threadLocalVar = 0;
//thread_local queue<int> q;

void threadFunction(int id)
{
    threadLocalVar = id;

    while (true)
    {
        cout << "Thread " << id << " has threadLocalVar = " << threadLocalVar << endl;

        this_thread::sleep_for(1s);
    }
}


int main() {
    std::thread t1(threadFunction, 1);
    std::thread t2(threadFunction, 2);
    t1.join();
    t2.join();

	return 0;
}
