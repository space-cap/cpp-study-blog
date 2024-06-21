#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>


void printMessage(const std::string& message) {
	std::cout << message << std::endl;
}

int main()
{
	std::thread t(printMessage, "스레드 1에서 보냅니다.");
	

	cout << "hello main" << endl;

	if(t.joinable())
	{
		t.join();
	}

}
