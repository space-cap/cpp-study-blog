#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>
#include "ThreadManager.h"

#include "RefCounting.h"
#include "Memory.h"
#include "Allocator.h"


#include <windows.h>
#include <iostream>
#include <vector>
#include <thread>

#include <iostream>
#include <vector>

// 풀에 사용할 객체 정의
class PooledObject {
public:
    void reset() {
        // 필요시 객체를 초기 상태로 재설정
    }
    void doSomething() {
        std::cout << "Doing something with the pooled object." << std::endl;
    }
    // 다른 메서드와 멤버...
};

// 객체 풀 클래스 정의
class fObjectPool {
public:
    PooledObject* acquire() {
        if (pool.empty()) {
            // 사용 가능한 객체가 없으면 새 객체 생성
            return new PooledObject();
        }
        else {
            // 풀에서 객체를 가져옴
            PooledObject* obj = pool.back();
            pool.pop_back();
            return obj;
        }
    }

    void release(PooledObject* obj) {
        obj->reset();  // 객체를 풀에 돌려놓기 전에 재설정
        pool.push_back(obj);
    }

    ~fObjectPool() {
        for (auto obj : pool) {
            delete obj;
        }
    }

private:
    std::vector<PooledObject*> pool;
};

// 사용 예제
int main() {
    fObjectPool pool;

    // 풀에서 객체를 가져옴
    PooledObject* obj1 = pool.acquire();
    obj1->doSomething();

    // 객체를 풀에 반환
    pool.release(obj1);

    // 다른 객체를 가져옴 (풀에서 같은 객체를 재사용할 수 있음)
    PooledObject* obj2 = pool.acquire();
    obj2->doSomething();

    // 객체를 풀에 반환
    pool.release(obj2);

    return 0;
}


