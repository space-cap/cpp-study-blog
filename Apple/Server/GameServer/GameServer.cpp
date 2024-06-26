#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>
#include "ThreadManager.h"



const int N = 100000;
std::vector<bool> isPrime(N + 1, true);
std::mutex mtx;

void sieveSegment(int start, int end) {
    for (int i = 2; i * i <= N; ++i) {
        if (isPrime[i]) {
            for (int j = max(i * i, (start + i - 1) / i * i); j <= end; j += i) {
                std::lock_guard<std::mutex> guard(mtx);
                isPrime[j] = false;
            }
        }
    }
}

int main() {
    int numThreads = std::thread::hardware_concurrency(); // 사용 가능한 하드웨어 스레드 수
    std::vector<std::thread> threads;

    int segmentSize = (N + numThreads - 1) / numThreads;

    isPrime[0] = isPrime[1] = false; // 0과 1은 소수가 아님

    for (int t = 0; t < numThreads; ++t) {
        int start = t * segmentSize;
        int end = min((t + 1) * segmentSize - 1, N);
        threads.emplace_back(sieveSegment, start, end);
    }

    for (auto& th : threads) {
        th.join();
    }

    int primeCount = 0;
    for (int i = 2; i <= N; ++i) {
        if (isPrime[i]) {
            ++primeCount;
        }
    }

    std::cout << "Number of primes less than or equal to " << N << " is: " << primeCount << std::endl;

    return 0;
}


