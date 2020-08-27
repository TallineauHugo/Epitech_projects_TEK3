//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// freeze
//

#include "Freeze.hpp"
#include "StatsManager.hpp"

bool Status::Freeze::update(float deltaTime)
{
	_lifeTime -= deltaTime;
	if (_lifeTime <= 0)
		return false;
	return true;
}

bool Status::Freeze::isStatus(Status status) const
{
	return _status == status;
}

bool Status::Freeze::canMove() const
{
	return false;
}

Status::Freeze::Freeze(Status status, float lifeTime, StatsManager *statsManager)
: _status(status), _lifeTime(lifeTime), _statsManager(statsManager)
{
	_statsManager->setDmgMultiplier(0.0);
}

Status::Freeze::~Freeze()
{
	_statsManager->setDmgMultiplier(1.0);
}