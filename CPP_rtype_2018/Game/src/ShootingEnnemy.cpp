#include <iostream>
#include "TimeManager.hpp"
#include "Bullet.hpp"
#include "EnnemySpaceShip.hpp"
#include "Event.hpp"
#include "ShootingEnnemy.hpp"

ShootingEnnemy::ShootingEnnemy(Vector2d pos) : EnnemySpaceShip(pos, 25, 1), SpaceShip(pos, 1, ENNEMY)
{
	_name += "ShootingEnnemy::";
	_velocity.x = -200;
	_hitbox.setSquareSize(Vector2d(50, 50));
	addEvent<ShootingEnnemy>(_events, OtterEngine::Event<ShootingEnnemy>("Collide", &ShootingEnnemy::collision, &ShootingEnnemy::collide));
	addEvent<ShootingEnnemy>(_events, OtterEngine::Event<ShootingEnnemy>("Always", &ShootingEnnemy::shoot, &ShootingEnnemy::always));
	_sprite->loadSpriteFromFile("ressources/texture/Wall.png");
}

ShootingEnnemy::~ShootingEnnemy()
{

}

EnnemySpaceShip *ShootingEnnemy::clone()
{
	return (new ShootingEnnemy(getPos()));
}

bool ShootingEnnemy::collide(OtterEngine::Engine *oe)
{
	return CollisionVerification(oe);
}

int ShootingEnnemy::collision(OtterEngine::Engine *oe)
{
	CollisionReaction(oe);
	oe->addObject(new ShootingEnnemy(Vector2d(2000, getPos().y)));
}

int ShootingEnnemy::shoot(OtterEngine::Engine *oe)
{
	float elapsedTime = TimeManager::getInstance()->getTotalTime();

	if (_lastShoot > elapsedTime || elapsedTime - _lastShoot > _cooldown) {
		oe->addObject(new Bullet(_hitbox.getPos(), Vector2d(-1000, 0), _camp));
		_lastShoot = elapsedTime;
	}
}

bool ShootingEnnemy::always(OtterEngine::Engine *oe)
{
	return true;
}

void ShootingEnnemy::updateEvents(OtterEngine::Engine *oe)
{
	for (int i = 0; i < _events.size(); i++)
	{
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}
