//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// poison
//

#include "Poison.hpp"
#include "StatsManager.hpp"

bool Status::Poison::update(float deltaTime)
{
	std::size_t amount;

	_lifeTime -= deltaTime;
	if (_lifeTime <= 0)
		return false;

	amount = (_statsManager->getMaxHp() / 8) * deltaTime;
	_statsManager->loseLife(amount);
	return true;
}

bool Status::Poison::isStatus(Status status) const
{
	return _status == status;
}

bool Status::Poison::canMove() const
{
	return true;
}

Status::Poison::Poison(Status status, float lifeTime, StatsManager *statsManager)
: _status(status), _lifeTime(lifeTime), _statsManager(statsManager)
{
	if (_statsManager->getType().first == Types::POISON || _statsManager->getType().first == Types::STEEL
			|| _statsManager->getType().second == Types::POISON || _statsManager->getType().second == Types::STEEL)
		_lifeTime = 0;
}

Status::Poison::~Poison()
{
}