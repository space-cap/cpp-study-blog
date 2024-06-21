#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>


void doWork() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "작업 완료!" << std::endl;
}

int main() {
    std::thread t(doWork);
    t.detach();
    std::cout << "스레드 분리됨." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}
