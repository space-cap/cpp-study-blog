#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>


// 비동기적으로 실행될 함수
int longComputation(int x) {
    std::this_thread::sleep_for(std::chrono::seconds(3)); // 긴 계산을 시뮬레이션
    return x * x;
}

int main() {
    // std::async를 사용하여 longComputation 함수를 비동기적으로 실행
    std::future<int> result = std::async(std::launch::async, longComputation, 10);

    // 다른 작업을 수행
    std::cout << "Computing...\n";

    // 결과를 기다림
    int value = result.get(); // 여기서 longComputation의 결과를 받음

    // 결과 출력
    std::cout << "Result: " << value << std::endl;

    return 0;
}

