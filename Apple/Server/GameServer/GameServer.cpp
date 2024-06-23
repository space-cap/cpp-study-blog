#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>


int64 Calculate()
{
	int64 sum = 0;

	for (int32 i = 0; i < 100; ++i)
	{
		sum += i;
	}

	return sum;
}

int main()
{
	int64 sum = Calculate();
	cout << sum << endl;

	// std::future
	{
		// 1) deferred -> lazy evaluation 지연해서 실행하세요
		// 2) async -> 별도의 쓰레드를 만들어서 실행하세요
		// 3) deferred | async -> 둘 중 알아서 골라주세요
		// 서버가 실행이 될 때 데이터 로딩에서 사용을 해 보는 것도 좋다.
		std::future<int64> future = std::async(std::launch::async, Calculate);

		// todo

		int64 sum = future.get();


		class Knight
		{
		public:
			int64 GetHp()
			{
				return 100;
			}
		};

		Knight knight;
		std::future<int64> future2 = std::async(std::launch::async, &Knight::GetHp, knight); // knight.GetHp()


	}

	return 0;
}
