//
// EPITECH PROJECT, 2018
// 
// File description:
// 
//

#pragma once

#include "IMutex.hpp"

class Mutex
{
public:
	Mutex();
	~Mutex();

	void lock();
	void unlock();
	void trylock();
	void wait();
	void signal();
	void broadcast();
private:
	pthread_mutex_t _mutex;
	pthread_cond_t _cond;
};
