#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>


void HelloThread()
{
	cout << "hello thread" << endl;
}

int main()
{
    thread t(HelloThread);

	cout << "hello main" << endl;

	if(t.joinable())
	{
		t.join();
	}

}
