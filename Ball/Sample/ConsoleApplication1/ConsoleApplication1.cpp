#include <iostream>
#include <cstring>

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
