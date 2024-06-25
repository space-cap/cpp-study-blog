#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>
#include "ThreadManager.h"

#include <atomic>
#include <thread>
#include <iostream>

class ReadWriteSpinLock {
private:
    std::atomic<int> readers_count;
    std::atomic<bool> writer;

public:
    ReadWriteSpinLock() : readers_count(0), writer(false) {}

    void lock_read() {
        while (true) {
            // 기다리는 동안 작성자가 없을 때까지 대기
            while (writer.load(std::memory_order_acquire)) {
                std::this_thread::yield(); // 잠깐 대기
            }

            readers_count.fetch_add(1, std::memory_order_acquire);

            // 작성자가 없는지 다시 확인
            if (!writer.load(std::memory_order_acquire)) {
                break;
            }

            readers_count.fetch_sub(1, std::memory_order_release);
        }
    }

    void unlock_read() {
        readers_count.fetch_sub(1, std::memory_order_release);
    }

    void lock_write() {
        while (writer.exchange(true, std::memory_order_acquire)) {
            std::this_thread::yield(); // 잠깐 대기
        }

        while (readers_count.load(std::memory_order_acquire) != 0) {
            std::this_thread::yield(); // 잠깐 대기
        }
    }

    void unlock_write() {
        writer.store(false, std::memory_order_release);
    }
};

// 테스트 예제
int main() {
    ReadWriteSpinLock rw_lock;

    // 읽기 작업
    auto reader = [&rw_lock](int id) {
        rw_lock.lock_read();
        std::cout << "Reader " << id << " is reading.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 읽기 작업 시뮬레이션
        rw_lock.unlock_read();
        };

    // 쓰기 작업
    auto writer = [&rw_lock](int id) {
        rw_lock.lock_write();
        std::cout << "Writer " << id << " is writing.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 쓰기 작업 시뮬레이션
        rw_lock.unlock_write();
        };

    // 여러 읽기/쓰기 스레드 생성
    std::thread readers[5], writers[2];
    for (int i = 0; i < 5; ++i) {
        readers[i] = std::thread(reader, i);
    }
    for (int i = 0; i < 2; ++i) {
        writers[i] = std::thread(writer, i);
    }

    // 스레드 조인
    for (int i = 0; i < 5; ++i) {
        readers[i].join();
    }
    for (int i = 0; i < 2; ++i) {
        writers[i].join();
    }

    return 0;
}

