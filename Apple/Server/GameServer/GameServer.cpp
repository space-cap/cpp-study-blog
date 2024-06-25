#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>



#include <atomic>
#include <iostream>

template<typename T>
class LockFreeQueue {
private:
    struct Node {
        T data;
        std::atomic<Node*> next;
        Node(T const& data) : data(data), next(nullptr) {}
    };

    std::atomic<Node*> head;
    std::atomic<Node*> tail;

public:
    LockFreeQueue() {
        Node* dummy = new Node(T());
        head.store(dummy);
        tail.store(dummy);
    }

    ~LockFreeQueue() {
        while (Node* node = head.load()) {
            head.store(node->next);
            delete node;
        }
    }

    void enqueue(T const& data) {
        Node* new_node = new Node(data);
        Node* old_tail = tail.load(std::memory_order_relaxed);

        while (true) {
            Node* next = old_tail->next.load(std::memory_order_relaxed);
            if (old_tail == tail.load(std::memory_order_relaxed)) {
                if (next == nullptr) {
                    if (old_tail->next.compare_exchange_weak(next, new_node, std::memory_order_release, std::memory_order_relaxed)) {
                        tail.compare_exchange_weak(old_tail, new_node, std::memory_order_release, std::memory_order_relaxed);
                        return;
                    }
                }
                else {
                    tail.compare_exchange_weak(old_tail, next, std::memory_order_release, std::memory_order_relaxed);
                }
            }
            else {
                old_tail = tail.load(std::memory_order_relaxed);
            }
        }
    }

    bool dequeue(T& result) {
        Node* old_head = head.load(std::memory_order_relaxed);

        while (true) {
            Node* old_tail = tail.load(std::memory_order_relaxed);
            Node* next = old_head->next.load(std::memory_order_relaxed);

            if (old_head == head.load(std::memory_order_relaxed)) {
                if (old_head == old_tail) {
                    if (next == nullptr) {
                        return false; // Queue is empty
                    }
                    tail.compare_exchange_weak(old_tail, next, std::memory_order_release, std::memory_order_relaxed);
                }
                else {
                    if (next == nullptr) {
                        return false;
                    }
                    result = next->data;
                    if (head.compare_exchange_weak(old_head, next, std::memory_order_release, std::memory_order_relaxed)) {
                        delete old_head;
                        return true;
                    }
                }
            }
            else {
                old_head = head.load(std::memory_order_relaxed);
            }
        }
    }
};

int main() {
    LockFreeQueue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    int value;
    while (queue.dequeue(value)) {
        std::cout << value << std::endl;
    }

    return 0;
}
