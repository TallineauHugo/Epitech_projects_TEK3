#include <iostream>
#include "Hitbox.hpp"
#include "Bullet.hpp"
#include "TimeManager.hpp"
#include "Object.hpp"
#include "Camp.hpp"
#include "SpaceShip.hpp"

SpaceShip::SpaceShip(Vector2d pos, float maxcooldown, CAMP camp) : Object(), _cooldown(maxcooldown), _camp(camp)
{
	_name += "SpaceShip::";
	_hitbox.setType(OtterEngine::Hitbox::SQUARE);
	_hitbox.setPos(pos);
	_hitbox.setSquareSize(Vector2d(70, 30));
	_lastShoot = 0;
}

SpaceShip::~SpaceShip()
{

}

int SpaceShip::shootBullet(OtterEngine::Engine *oe)
{
	float elapsedTime = TimeManager::getInstance()->getTotalTime();
	
	if (_lastShoot > elapsedTime || elapsedTime - _lastShoot > _cooldown) {
		oe->addObject(new Bullet(_hitbox.getPos(), Vector2d(1000, 0), _camp));
		_lastShoot = elapsedTime;
	}
}

float SpaceShip::getCooldown()
{
	return _cooldown;
}

void SpaceShip::setCooldown(float cooldown)
{
	_cooldown = cooldown;
	if (_cooldown < 0.1)
		_cooldown = 0.1;
}

CAMP SpaceShip::getCamp()
{
	return _camp;
}

void SpaceShip::setCamp(CAMP camp)
{
	_camp = camp;
}

void SpaceShip::updateEvents(OtterEngine::Engine *oe)
{
	for (int i = 0; i < _events.size(); i++)
	{
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}
