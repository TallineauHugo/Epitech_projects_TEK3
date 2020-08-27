#include "TimeManager.hpp"

TimeManager::TimeManager(): _totalTime(0)
{
}

TimeManager::~TimeManager()
{
}

void TimeManager::update()
{
	this->_deltaTime = this->_clock.restart().asSeconds();
	_totalTime += this->_deltaTime;
}

float TimeManager::getDeltaTime()
{
	return this->_deltaTime;
}

float TimeManager::getTotalTime()
{
	return this->_totalTime;
}