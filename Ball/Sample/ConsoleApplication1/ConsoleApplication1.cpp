#include <iostream>
#include <cstring>
#include <vector>


struct Item
{
    int id;
};

struct weapon : public Item
{
    int hp;
    int mp;
};


struct Packet {
    int id;
    float value;
    std::string message;
    std::vector<weapon> data;
};







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
