#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>
#include "ThreadManager.h"


#include <winsock2.h>
#include <iostream>

#define INVALID_SOCKET  (SOCKET)(~0)

int main() {
    WSADATA wsaData;
    SOCKET sock;

    // Winsock 초기화
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup 실패.\n";
        return 1;
    }

    // 소켓 생성
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "socket()에서 오류 발생: " << WSAGetLastError() << "\n";
        WSACleanup();
        return 1;
    }

    std::cout << "소켓이 성공적으로 생성되었습니다.\n";

    // 정리
    closesocket(sock);
    WSACleanup();

    return 0;
}
