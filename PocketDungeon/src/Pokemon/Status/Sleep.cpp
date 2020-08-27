//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// sleep
//

#include "Sleep.hpp"
#include "StatsManager.hpp"

bool Status::Sleep::update(float deltaTime)
{
	_lifeTime -= deltaTime;
	if (_lifeTime <= 0)
		return false;
	return true;
}

bool Status::Sleep::isStatus(Status status) const
{
	return _status == status;
}

bool Status::Sleep::canMove() const
{
	return false;
}

Status::Sleep::Sleep(Status status, float lifeTime, StatsManager *statsManager) 
: _status(status), _lifeTime(lifeTime), _statsManager(statsManager)
{
}

Status::Sleep::~Sleep()
{
}