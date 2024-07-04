#include <iostream>
#include <string>

int main() {
    std::wstring wideStr = L"Hello, 세계!";

    // wstring.data() 사용하여 내부 데이터 접근
    const wchar_t* data = wideStr.data();

    // 출력
    std::wcout << L"wstring: " << wideStr << std::endl;
    std::wcout << L"data(): " << data << std::endl;

    return 0;
}
