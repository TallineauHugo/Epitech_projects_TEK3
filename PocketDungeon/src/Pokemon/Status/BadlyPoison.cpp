//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// badly poison
//

#include "BadlyPoison.hpp"
#include "StatsManager.hpp"

bool Status::BadlyPoison::update(float deltaTime)
{
	std::size_t amount;
	static float total = 1.0;

	_lifeTime -= deltaTime;
	if (_lifeTime <= 0)
		return false;
	total += deltaTime;

	amount = ((_statsManager->getMaxHp() * (std::size_t)total) / 16) * deltaTime;
	_statsManager->loseLife(amount);
	return true;
}

bool Status::BadlyPoison::isStatus(Status status) const
{
	return _status == status;
}

bool Status::BadlyPoison::canMove() const
{
	return true;
}

Status::BadlyPoison::BadlyPoison(Status status, float lifeTime, StatsManager *statsManager) 
: _status(status), _lifeTime(lifeTime), _statsManager(statsManager)
{
	if (_statsManager->getType().first == Types::POISON || _statsManager->getType().first == Types::STEEL
			|| _statsManager->getType().second == Types::POISON || _statsManager->getType().second == Types::STEEL)
		_lifeTime = 0;
}

Status::BadlyPoison::~BadlyPoison()
{
}