#include <iostream>
#include <string>

int main() {
    std::wstring wideStr = L"Hello, ����!";

    // wstring.data() ����Ͽ� ���� ������ ����
    const wchar_t* data = wideStr.data();

    // ���
    std::wcout << L"wstring: " << wideStr << std::endl;
    std::wcout << L"data(): " << data << std::endl;

    return 0;
}
