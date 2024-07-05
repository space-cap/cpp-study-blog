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
    char destination[20];  // ����� ū �迭�� �غ�

    // �޸� ����
    memcpy(destination, source, strlen(source) + 1);  // �� ���� ���� ����

    // ���
    std::cout << "Source: " << source << std::endl;
    std::cout << "Destination: " << destination << std::endl;

    return 0;
}
