//
// EPITECH PROJECT, 2019
// pocket dungeon
// File description:
// stat debuff
//

#include "StatDebuff.hpp"
#include "StatsManager.hpp"

bool Status::StatDebuff::update(float deltaTime)
{
	_lifeTime -= deltaTime;
	if (_lifeTime <= 0)
		return false;

	return true;
}

bool Status::StatDebuff::isStatus(Status status) const
{
	return false;
}

bool Status::StatDebuff::canMove() const
{
	return true;
}

Status::StatDebuff::StatDebuff(std::string stat, float lifeTime, StatsManager *statsManager)
: _stat(stat), _lifeTime(lifeTime), _statsManager(statsManager)
{
	_statsManager->applyBuff(stat, -1);
}

Status::StatDebuff::~StatDebuff()
{
	_statsManager->applyBuff(_stat, 1);
}