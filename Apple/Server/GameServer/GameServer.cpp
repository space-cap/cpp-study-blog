#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>


// 스레드에서 실행될 함수
void computeSquare(std::promise<int> promise, int x) {
    std::this_thread::sleep_for(std::chrono::seconds(3)); // 긴 계산을 시뮬레이션
    promise.set_value(x * x); // 결과를 promise에 설정
}

int main() {
    // std::promise와 연결된 std::future 객체 생성
    std::promise<int> promise;
    std::future<int> result = promise.get_future();

    // 새로운 스레드에서 computeSquare 함수 실행
    std::thread t(computeSquare, std::move(promise), 10);

    // 다른 작업을 수행
    std::cout << "Computing...\n";

    // 결과를 기다림
    int value = result.get(); // 여기서 computeSquare 함수의 결과를 받음

    // 결과 출력
    std::cout << "Result: " << value << std::endl;

    t.join(); // 스레드가 종료될 때까지 기다림

    return 0;
}


