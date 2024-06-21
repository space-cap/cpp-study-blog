#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <thread>
#include <atomic>
#include <mutex>

vector<int32> v;
mutex m;

// RAII(Resource Acquisition Is Initialization) 패턴
template<typename T>
class LockGuard
{
public:
	LockGuard(T& m)
	{
		_mutex = &m;
		_mutex->lock();
	}

	~LockGuard()
	{
		_mutex->unlock();
	}

private:
	T* _mutex;
};


void Push()
{
	for(int32 i=0; i<1000; ++i)
	{
		//m.lock();
		//LockGuard<std::mutex> lockGuard(m);
		std::lock_guard<std::mutex> lockGuard(m);
		v.push_back(i);
		//m.unlock();
	}
}



int main()
{
	v.reserve(20000);

	thread t1(Push);
	thread t2(Push);

	t1.join();
	t2.join();

	cout << v.size() << endl;

	return 0;
}
