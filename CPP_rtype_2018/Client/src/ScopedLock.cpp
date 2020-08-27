//
// EPITECH PROJECT, 2018
// 
// File description:
// 
//

#include "ScopedLock.hpp"

ScopedLock::ScopedLock(Mutex &mutex) : _mutex(mutex)
{
	_mutex.lock();
}

ScopedLock::~ScopedLock()
{
	_mutex.unlock();
}
