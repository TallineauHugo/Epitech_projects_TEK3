//
// EPITECH PROJECT, 2019
// pocket dungeon
// File description:
// stat buff
//

#include "StatBuff.hpp"
#include "StatsManager.hpp"

bool Status::StatBuff::update(float deltaTime)
{
	_lifeTime -= deltaTime;
	if (_lifeTime <= 0)
		return false;

	return true;
}

bool Status::StatBuff::isStatus(Status status) const
{
	return false;
}

bool Status::StatBuff::canMove() const
{
	return true;
}

Status::StatBuff::StatBuff(std::string stat, float lifeTime, StatsManager *statsManager)
: _stat(stat), _lifeTime(lifeTime), _statsManager(statsManager)
{
	_statsManager->applyBuff(stat, 1);
}

Status::StatBuff::~StatBuff()
{
	_statsManager->applyBuff(_stat, -1);
}