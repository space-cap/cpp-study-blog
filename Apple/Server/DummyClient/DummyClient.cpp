#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")


// TCPClient.cpp


int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    const char* message = "Hello, Server!";
    char buffer[1024];
    int recvSize;

    // Winsock 초기화
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
        return 1;
    }

    // 소켓 생성
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // 서버 주소 구조체 설정
    serverAddr.sin_family = AF_INET;
    ::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
    serverAddr.sin_port = htons(54000);

    // 서버에 연결
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connect failed: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Connected to server!" << std::endl;

    // 데이터 전송
    if (send(clientSocket, message, strlen(message), 0) == SOCKET_ERROR) {
        std::cerr << "Send failed: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // 데이터 수신 (옵션)
    recvSize = recv(clientSocket, buffer, 1024, 0);
    if (recvSize > 0) {
        buffer[recvSize] = '\0';
        std::cout << "Received: " << buffer << std::endl;
    }
    else if (recvSize == 0) {
        std::cout << "Connection closed." << std::endl;
    }
    else {
        std::cerr << "Recv failed: " << WSAGetLastError() << std::endl;
    }

    // 소켓 닫기
    closesocket(clientSocket);
    WSACleanup();
    return 0;
}




