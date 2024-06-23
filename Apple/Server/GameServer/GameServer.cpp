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


void PromiseWorker(std::promise<string>&& promise)
{
	promise.set_value("secret message");
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

		int64 sum = future.get(); // 이제 결과물이 필요해.

	}

	// std::promise
	{
		// 미래(std::future)에 결과물을 반환해 줄꺼라 약속(std::promise)해줘 ~ 계약서??
		std::promise<string> promise;
		std::future<string> future = promise.get_future();

		thread t(PromiseWorker, std::move(promise));

		string message = future.get();
		cout << message << endl;


		t.join();
	}



	return 0;
}
