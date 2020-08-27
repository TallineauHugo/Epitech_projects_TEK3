#pragma once

#include <queue>
#include "ScopedLock.hpp"

template <typename T>
class SafeQueue
{
public:
	SafeQueue();
	~SafeQueue();

	const Mutex &getMutex() const;
	
	void push(T value);	
	bool tryPop(T &value);
	T pop();
private:
	std::queue<T> _queue;
	Mutex _mutex;
};
