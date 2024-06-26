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
#include <memory>

class MyClass {
public:
    MyClass() { std::cout << "MyClass Constructor" << std::endl; }
    ~MyClass() { std::cout << "MyClass Destructor" << std::endl; }
    void display() { std::cout << "MyClass display" << std::endl; }
};

int main() {
    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>();
    std::weak_ptr<MyClass> weakPtr = ptr1;

    if (auto sharedPtr = weakPtr.lock()) { // weak_ptr에서 shared_ptr 얻기
        sharedPtr->display();
        std::cout << "Use count: " << sharedPtr.use_count() << std::endl;
    }
    else {
        std::cout << "Object no longer exists" << std::endl;
    }

    return 0; // ptr1이 범위를 벗어나면서 MyClass의 소멸자가 호출됩니다.
}


