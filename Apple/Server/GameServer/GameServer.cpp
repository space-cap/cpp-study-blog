#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>

std::atomic<int32>(sum){};

void add()
{
	for(int32 i=0; i<100'0000; ++i)
	{
        sum += i;
	}
}


void sub()
{
    for (int32 i = 0; i < 100'0000; ++i)
    {
        sum -= i;
    }
}




int main() {

    add();
    sub();

    cout << sum << endl;

    std::thread t1(add);
    std::thread t2(sub);

    t1.join();
    t2.join();

    cout << sum << endl;


    return 0;
}
