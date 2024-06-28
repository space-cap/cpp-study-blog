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


#include <windows.h>
#include <iostream>
#include <vector>
#include <thread>

typedef struct _MY_DATA {
    SLIST_ENTRY ListEntry;
    int Data;
} MY_DATA, * PMY_DATA;

SLIST_HEADER ListHead;

void InsertData(int data) {
    PMY_DATA myData = (PMY_DATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(MY_DATA));
    myData->Data = data;
    InterlockedPushEntrySList(&ListHead, &myData->ListEntry);
    std::cout << "Inserted: " << data << std::endl;
}

void RemoveData() {
    PSLIST_ENTRY pListEntry = InterlockedPopEntrySList(&ListHead);
    if (pListEntry != NULL) {
        PMY_DATA pData = CONTAINING_RECORD(pListEntry, MY_DATA, ListEntry);
        std::cout << "Removed: " << pData->Data << std::endl;
        HeapFree(GetProcessHeap(), 0, pData);
    }
    else {
        std::cout << "List is empty" << std::endl;
    }
}

void InsertThread(int start, int end) {
    for (int i = start; i <= end; ++i) {
        InsertData(i);
    }
}

void RemoveThread(int count) {
    for (int i = 0; i < count; ++i) {
        RemoveData();
    }
}

int main() {
    // 단일 연결 리스트 초기화
    InitializeSListHead(&ListHead);

    // 삽입 스레드 생성
    std::thread insertThread1(InsertThread, 1, 10);
    std::thread insertThread2(InsertThread, 11, 20);

    // 삽입 스레드 종료 대기
    insertThread1.join();
    insertThread2.join();

    // 제거 스레드 생성
    std::thread removeThread1(RemoveThread, 10);
    std::thread removeThread2(RemoveThread, 10);

    // 제거 스레드 종료 대기
    removeThread1.join();
    removeThread2.join();

    return 0;
}

