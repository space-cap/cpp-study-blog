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
#include <cmath>

bool isPrime(int number) {
    if (number <= 1) return false; // 1 이하는 소수가 아님
    if (number <= 3) return true;  // 2, 3은 소수임

    if (number % 2 == 0 || number % 3 == 0) return false; // 2나 3으로 나눠지는 수는 소수가 아님

    for (int i = 5; i * i <= number; i += 6) {
        if (number % i == 0 || number % (i + 2) == 0) return false;
    }

    return true;
}

int main() {
    int n;
    std::cout << "Enter a number: ";
    std::cin >> n;

    if (isPrime(n)) {
        std::cout << n << " is a prime number." << std::endl;
    }
    else {
        std::cout << n << " is not a prime number." << std::endl;
    }

    return 0;
}
