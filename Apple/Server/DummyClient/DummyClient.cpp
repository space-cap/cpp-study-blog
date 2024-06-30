#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

const int PORT = 7777;
const std::string HOST = "127.0.0.1";

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    sockaddr_in serverAddr;
    char buffer[1024];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
        return 1;
    }

    // Create a socket
    clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Setup the server address structure
    ::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    ::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
    serverAddr.sin_port = htons(PORT);

    std::string message = "Hello, UDP Server!";
    sendto(clientSocket, message.c_str(), message.size(), 0, (sockaddr*)&serverAddr, sizeof(serverAddr));

    int serverAddrSize = sizeof(serverAddr);
    int receivedBytes = recvfrom(clientSocket, buffer, sizeof(buffer), 0, (sockaddr*)&serverAddr, &serverAddrSize);
    if (receivedBytes == SOCKET_ERROR) {
        std::cerr << "recvfrom failed: " << WSAGetLastError() << std::endl;
    }
    else {
        buffer[receivedBytes] = '\0';
        std::cout << "Reply: " << buffer << std::endl;
    }

    // Cleanup
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}


