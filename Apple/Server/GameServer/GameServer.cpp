#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>



template<typename T>
class LockFreeStack {
private:
    struct Node {
        T data;
        Node* next;
        Node(T const& data) : data(data), next(nullptr) {}
    };

    std::atomic<Node*> head;

public:
    LockFreeStack() : head(nullptr) {}

    void push(T const& data) {
        Node* new_node = new Node(data);
        new_node->next = head.load(std::memory_order_relaxed);
        while (!head.compare_exchange_weak(new_node->next, new_node, std::memory_order_release, std::memory_order_relaxed)) {
            // CAS 실패, new_node->next 업데이트, 재시도
        }
    }

    bool pop(T& result) {
        Node* old_head = head.load(std::memory_order_relaxed);
        while (old_head && !head.compare_exchange_weak(old_head, old_head->next, std::memory_order_acquire, std::memory_order_relaxed)) {
            // CAS 실패, old_head 업데이트, 재시도
        }
        if (old_head) {
            result = old_head->data;
            delete old_head;
            return true;
        }
        return false; // 스택이 비어 있음
    }
};

int main() {
    LockFreeStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    int value;
    while (stack.pop(value)) {
        std::cout << value << std::endl;
    }

    return 0;
}
