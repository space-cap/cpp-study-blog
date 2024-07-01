#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>
#include "ThreadManager.h"

#include "RefCounting.h"
#include "Memory.h"
#include "Allocator.h"
#include "TypeCast.h"
#include <iostream>
#include <type_traits>


#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")



#include <winsock2.h>
#include <iostream>

int main() {
    WSADATA wsaData;
    SOCKET sock;
    sockaddr_in server;
    u_long mode = 1;

    WSAStartup(MAKEWORD(2, 2), &wsaData);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    ioctlsocket(sock, FIONBIO, &mode); // Set non-blocking mode
    ::inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
    server.sin_family = AF_INET;
    server.sin_port = htons(12345);

    connect(sock, (struct sockaddr*)&server, sizeof(server));

    char message[1000], server_reply[2000];
    int message_len, reply_len;

    while (true) {
        std::cout << "Enter message: ";
        std::cin.getline(message, sizeof(message));
        message_len = strlen(message);

        send(sock, message, message_len, 0);

        while (true) {
            reply_len = recv(sock, server_reply, sizeof(server_reply), 0);
            if (reply_len > 0) {
                server_reply[reply_len] = '\0';
                std::cout << "Server reply: " << server_reply << std::endl;
                break;
            }
            else if (reply_len == SOCKET_ERROR) {
                if (WSAGetLastError() == WSAEWOULDBLOCK) {
                    // No data available yet, continue processing other tasks
                    Sleep(100); // Small delay to prevent busy-waiting
                    continue;
                }
                else {
                    std::cerr << "Recv failed: " << WSAGetLastError() << std::endl;
                    break;
                }
            }
        }
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}



