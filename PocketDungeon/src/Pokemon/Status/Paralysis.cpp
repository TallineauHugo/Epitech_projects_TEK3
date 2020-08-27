//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// paralysis
//

#include "Paralysis.hpp"
#include "StatsManager.hpp"

bool Status::Paralysis::update(float deltaTime)
{
	_lifeTime -= deltaTime;
	if (_lifeTime <= 0)
		return false;
	return true;
}

bool Status::Paralysis::isStatus(Status status) const
{
	return _status == status;
}

bool Status::Paralysis::canMove() const
{
	return true;
}

Status::Paralysis::Paralysis(Status status, float lifeTime, StatsManager *statsManager) 
: _status(status), _lifeTime(lifeTime), _statsManager(statsManager)
{
	if (_statsManager->getType().first == Types::ELECTRIC || _statsManager->getType().second == Types::ELECTRIC)
		_lifeTime = 0;
	_statsManager->applyBuff(SPEED, -2);
}

Status::Paralysis::~Paralysis()
{
	_statsManager->applyBuff(SPEED, 2);
}