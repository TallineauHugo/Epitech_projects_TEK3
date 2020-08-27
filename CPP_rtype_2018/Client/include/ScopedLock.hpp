//
// EPITECH PROJECT, 2018
// 
// File description:
// 
//

#pragma once

#include "Mutex.hpp"

class ScopedLock
{
public:
	ScopedLock(Mutex &mutex);
	~ScopedLock();
private:
	Mutex &_mutex;
};
