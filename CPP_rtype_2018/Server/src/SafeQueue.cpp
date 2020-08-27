#include <thread>
#include <string>
#include "SafeQueue.hpp"

template <typename T>
SafeQueue<T>::SafeQueue()
{}

template <typename T>
SafeQueue<T>::~SafeQueue()
{}

template <typename T>
void SafeQueue<T>::push(T value)
{
	ScopedLock lock(_mutex);

	_queue.push(value);
	_mutex.signal();
}

template <typename T>
bool SafeQueue<T>::tryPop(T &value)
{
	ScopedLock lock(_mutex);

	if (_queue.empty())
		return false;
	value = _queue.front();
	_queue.pop();
	return true;
}

template <typename T>
T SafeQueue<T>::pop()
{
	T value;
	
	ScopedLock lock(_mutex);

	while (_queue.empty())
		_mutex.wait();
	value = _queue.front();
	_queue.pop();
	return value;
}

template <typename T>
const Mutex &SafeQueue<T>::getMutex() const
{
	return _mutex;
}

template class SafeQueue<std::string>;
