//
// EPITECH PROJECT, 2018
// 
// File description:
// 
//

#pragma once

#include <pthread.h>

class IMutex
{
public:
	virtual ~IMutex() = default;
	virtual void lock() = 0;
	virtual void unlock() = 0;
	virtual void trylock() = 0;
};
