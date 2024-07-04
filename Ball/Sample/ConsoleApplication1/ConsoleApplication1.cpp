#include <iostream>
#include <cstring>

int main() {
    char source[] = "Hello, World!";
    char destination[20];  // 충분히 큰 배열을 준비

    // 메모리 복사
    memcpy(destination, source, strlen(source) + 1);  // 널 종결 문자 포함

    // 출력
    std::cout << "Source: " << source << std::endl;
    std::cout << "Destination: " << destination << std::endl;

    return 0;
}
