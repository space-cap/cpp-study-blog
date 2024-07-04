#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <Mswsock.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")

void CALLBACK CompletionRoutine(DWORD dwError, DWORD cbTransferred, LPWSAOVERLAPPED lpOverlapped, DWORD dwFlags) {
    std::cout << "WSASend completed with error: " << dwError << " and bytes transferred: " << cbTransferred << std::endl;
}

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return 1;
    }

    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET) {
        std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // 서버 포트
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 서버 IP

    if (connect(s, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed with error: " << WSAGetLastError() << std::endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    char sendData[] = "Hello, World!";
    WSABUF wsaBuf;
    wsaBuf.buf = sendData;
    wsaBuf.len = sizeof(sendData);

    DWORD bytesSent = 0;
    WSAOVERLAPPED overlapped = { 0 };

    if (WSASend(s, &wsaBuf, 1, &bytesSent, 0, &overlapped, CompletionRoutine) == SOCKET_ERROR) {
        if (WSAGetLastError() != WSA_IO_PENDING) {
            std::cerr << "WSASend failed with error: " << WSAGetLastError() << std::endl;
            closesocket(s);
            WSACleanup();
            return 1;
        }
    }

    // 비동기 작업이 완료될 때까지 대기
    SleepEx(INFINITE, TRUE);

    closesocket(s);
    WSACleanup();

    return 0;
}
