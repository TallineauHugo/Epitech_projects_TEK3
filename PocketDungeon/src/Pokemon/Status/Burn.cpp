//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// burn
//

#include "Burn.hpp"
#include "StatsManager.hpp"

bool Status::Burn::update(float deltaTime)
{
	std::size_t amount;

	_lifeTime -= deltaTime;
	if (_lifeTime <= 0)
		return false;
	
	amount = (_statsManager->getMaxHp() / 16) * deltaTime;
	_statsManager->loseLife(amount);
	return true;
}

bool Status::Burn::isStatus(Status status) const
{
	return _status == status;
}

bool Status::Burn::canMove() const
{
	return true;
}

Status::Burn::Burn(Status status, float lifeTime, StatsManager *statsManager)
: _status(status), _lifeTime(lifeTime), _statsManager(statsManager)
{
	if (_statsManager->getType().first == Types::FIRE || _statsManager->getType().second == Types::FIRE)
		_lifeTime = 0;
	_statsManager->applyBuff(ATK, -2);
}

Status::Burn::~Burn()
{
	_statsManager->applyBuff(ATK, 2);
}