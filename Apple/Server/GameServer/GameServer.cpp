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
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#define MAX_CLIENTS 10

int main() {
    WSADATA wsaData;
    SOCKET listenSocket, clientSocket[MAX_CLIENTS];
    struct sockaddr_in server, client;
    WSAEVENT events[MAX_CLIENTS + 1];
    WSANETWORKEVENTS networkEvents;
    int addrlen, new_socket, i, eventIndex;
    char buffer[1024];
    int valread;

    WSAStartup(MAKEWORD(2, 2), &wsaData);

    listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket == INVALID_SOCKET) {
        printf("Socket creation failed. Error: %d\n", WSAGetLastError());
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(12345);

    if (::bind(listenSocket, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed. Error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    if (listen(listenSocket, 3) == SOCKET_ERROR) {
        printf("Listen failed. Error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    for (i = 0; i < MAX_CLIENTS; i++) {
        clientSocket[i] = INVALID_SOCKET;
    }

    WSAEVENT listenEvent = WSACreateEvent();
    WSAEventSelect(listenSocket, listenEvent, FD_ACCEPT | FD_CLOSE);

    events[0] = listenEvent;

    while (TRUE) {
        eventIndex = WSAWaitForMultipleEvents(MAX_CLIENTS + 1, events, FALSE, WSA_INFINITE, FALSE);
        if (eventIndex == WSA_WAIT_FAILED) {
            printf("WSAWaitForMultipleEvents failed. Error: %d\n", WSAGetLastError());
            break;
        }

        eventIndex -= WSA_WAIT_EVENT_0;
        WSAEnumNetworkEvents((eventIndex == 0) ? listenSocket : clientSocket[eventIndex - 1], events[eventIndex], &networkEvents);

        if (networkEvents.lNetworkEvents & FD_ACCEPT) {
            addrlen = sizeof(struct sockaddr_in);
            new_socket = accept(listenSocket, (struct sockaddr*)&client, &addrlen);
            if (new_socket == INVALID_SOCKET) {
                printf("Accept failed. Error: %d\n", WSAGetLastError());
                continue;
            }
            printf("New connection. Socket FD: %d, IP: %s, Port: %d\n", new_socket, inet_ntoa(client.sin_addr), ntohs(client.sin_port));

            for (i = 0; i < MAX_CLIENTS; i++) {
                if (clientSocket[i] == INVALID_SOCKET) {
                    clientSocket[i] = new_socket;
                    WSAEVENT clientEvent = WSACreateEvent();
                    WSAEventSelect(new_socket, clientEvent, FD_READ | FD_CLOSE);
                    events[i + 1] = clientEvent;
                    break;
                }
            }
        }

        for (i = 0; i < MAX_CLIENTS; i++) {
            if (networkEvents.lNetworkEvents & FD_READ) {
                valread = recv(clientSocket[i], buffer, sizeof(buffer), 0);
                if (valread > 0) {
                    buffer[valread] = '\0';
                    printf("Received: %s\n", buffer);
                }
                else if (valread == 0 || WSAGetLastError() == WSAECONNRESET) {
                    printf("Host disconnected. Socket FD: %d\n", clientSocket[i]);
                    closesocket(clientSocket[i]);
                    WSACloseEvent(events[i + 1]);
                    clientSocket[i] = INVALID_SOCKET;
                }
            }
        }

        if (networkEvents.lNetworkEvents & FD_CLOSE) {
            printf("Listening socket closed.\n");
            break;
        }
    }

    closesocket(listenSocket);
    WSACleanup();
    return 0;
}



