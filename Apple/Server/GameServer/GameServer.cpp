#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>




// [][][][][][]    [][][][][][]    [][][][][][]     [][][][][][]
// 메모리에서 캐시로 데이터를 가지고 올 때 인접한 영역도 같이 가지고 오는데
// i j 로 하면 바로 옆에 있는 값을 가지고 와서 빠르지만
// j i 로 하면 가지고 오는 비용이 i j 보다 많이 발생이 된다.

int32 buffer[10000][10000];


int main()
{
	memset(buffer, 0, sizeof(buffer));

	{
		uint64 start = GetTickCount64();

		int64 sum = 0;
		for(int32 i=0; i< 10000; ++i)
		{
			for(int32 j=0;j<10000;++j)
			{
				sum += buffer[i][j];
			}
		}

		uint64 end = GetTickCount64();
		cout << "Elapsed Tick " << (end - start) << endl;
	}


	{
		uint64 start = GetTickCount64();

		int64 sum = 0;
		for (int32 i = 0; i < 10000; ++i)
		{
			for (int32 j = 0; j < 10000; ++j)
			{
				sum += buffer[j][i];
			}
		}

		uint64 end = GetTickCount64();
		cout << "Elapsed Tick " << (end - start) << endl;
	}

    return 0;
}


