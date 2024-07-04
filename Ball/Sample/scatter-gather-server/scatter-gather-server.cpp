#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")
int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        return 1;
    }

    SOCKET listeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listeningSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // 서버 포트
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listeningSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed with error: " << WSAGetLastError() << std::endl;
        closesocket(listeningSocket);
        WSACleanup();
        return 1;
    }

    if (listen(listeningSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed with error: " << WSAGetLastError() << std::endl;
        closesocket(listeningSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Waiting for connections..." << std::endl;

    SOCKET clientSocket = accept(listeningSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Accept failed with error: " << WSAGetLastError() << std::endl;
        closesocket(listeningSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Client connected." << std::endl;

    char recvBuf1[256]{};
    char recvBuf2[256]{};
    WSABUF wsaBuf[2];
    wsaBuf[0].buf = recvBuf1;
    wsaBuf[0].len = sizeof(recvBuf1);
    wsaBuf[1].buf = recvBuf2;
    wsaBuf[1].len = sizeof(recvBuf2);

    DWORD bytesReceived = 0;
    WSAOVERLAPPED overlapped = { 0 };

    if (WSARecv(clientSocket, wsaBuf, 2, &bytesReceived, 0, &overlapped, NULL) == SOCKET_ERROR) {
        int error = WSAGetLastError();
        if (error != WSA_IO_PENDING) {
            std::cerr << "WSARecv failed with error: " << error << std::endl;
            closesocket(clientSocket);
            closesocket(listeningSocket);
            WSACleanup();
            return 1;
        }
    }

    // 비동기 작업이 완료될 때까지 대기
    SleepEx(INFINITE, TRUE);

    std::cout << "Received data in buffer 1: " << std::string(recvBuf1, 0, bytesReceived) << std::endl;
    std::cout << "Received data in buffer 2: " << std::string(recvBuf2, 0, bytesReceived) << std::endl;

    closesocket(clientSocket);
    closesocket(listeningSocket);
    WSACleanup();

    return 0;
}

