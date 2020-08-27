//
// EPITECH PROJECT, 2018
// 
// File description:
// 
//

#include "Mutex.hpp"

Mutex::Mutex()
{
	pthread_mutex_init(&_mutex, NULL);
	pthread_cond_init(&_cond, NULL);
}

Mutex::~Mutex()
{
}

void Mutex::lock()
{
	pthread_mutex_lock(&_mutex);
}

void Mutex::unlock()
{
	pthread_mutex_unlock(&_mutex);
}

void Mutex::trylock()
{
	pthread_mutex_trylock(&_mutex);
}

void Mutex::wait()
{
	pthread_cond_wait(&_cond, &_mutex);
}

void Mutex::signal()
{
	pthread_cond_signal(&_cond);
}

void Mutex::broadcast()
{
	pthread_cond_broadcast(&_cond);
}
