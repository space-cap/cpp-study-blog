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
#include "TypeCast.h"
#include <iostream>
#include <type_traits>

template <typename Target, typename Source>
constexpr Target dynamic_cast_checked(Source* src) {
    static_assert(std::is_base_of_v<Source, std::remove_pointer_t<Target>> || std::is_base_of_v<std::remove_pointer_t<Target>, Source>, "Types must be related");
    return dynamic_cast<Target>(src);
}

class Base {
public:
    virtual ~Base() = default;
};
class Derived : public Base {};
class Unrelated {};

int main() {
    Base* base = new Base();
    Derived* derived = new Derived();
    Unrelated* unrelated = new Unrelated();

    // 올바른 캐스트
    Base* b1 = dynamic_cast_checked<Base*>(derived); // 성공
    Derived* d1 = dynamic_cast_checked<Derived*>(base); // 런타임에 실패할 수 있음

    // 잘못된 캐스트 (주석 처리됨)
    // Unrelated* u = dynamic_cast_checked<Unrelated*>(base); // 컴파일 오류: 관련 없는 타입

    delete base;
    delete derived;
    delete unrelated;

    return 0;
}

