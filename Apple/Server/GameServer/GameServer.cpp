#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>



int main()
{
	std::thread t([] {
		std::cout << "스레드에서 보냅니다." << std::endl;
		});
	

	cout << "hello main" << endl;

	if(t.joinable())
	{
		t.join();
	}

}
