#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>
#include "ThreadManager.h"

#include <iostream>
#include <vector>

int countPrimes(int n) {
    if (n <= 1) return 0;

    std::vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false; // 0과 1은 소수가 아님

    for (int i = 2; i * i <= n; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }

    int primeCount = 0;
    for (int i = 2; i <= n; ++i) {
        if (isPrime[i]) {
            ++primeCount;
        }
    }

    return primeCount;
}

int main() {
    int n = 10000;
    int primeCount = countPrimes(n);
    std::cout << "Number of primes less than or equal to " << n << " is: " << primeCount << std::endl;

    return 0;
}


