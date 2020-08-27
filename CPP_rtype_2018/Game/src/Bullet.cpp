#include <iostream>
#include "WindowManager.hpp"
#include "Object.hpp"
#include "Bullet.hpp"
#include "Camp.hpp"
#include "Hitbox.hpp"

Bullet::Bullet(Vector2d pos, Vector2d velocity, CAMP camp) : Object(), _camp(camp)
{	
	_hitbox.setPos(pos);
	_velocity = velocity;
	_name += "Bullet::";
	_hitbox.setType(OtterEngine::Hitbox::SQUARE);
	_hitbox.setSquareSize(Vector2d(20, 20));
	_sprite->loadSpriteFromFile("ressources/texture/Wall.png");
	addEvent<Bullet>(_events, OtterEngine::Event<Bullet>("OutOfScreen", &Bullet::outOfScreenReaction, &Bullet::outOfScreenVerification));
}

Bullet::~Bullet()
{

}

bool Bullet::outOfScreenVerification(OtterEngine::Engine *oe)
{
	if (getPos().x - 100 > WindowManager::getInstance()->getView()->getPosition().x + WindowManager::getInstance()->getView()->getSize().x  / 2)
		return true;
	return false;
}

int Bullet::outOfScreenReaction(OtterEngine::Engine *oe)
{
	OtterEngine::SpritesManager::getInstance()->removeSprite(_sprite);
	oe->removeObject(oe->getIndex(this));
}

void Bullet::setCamp(CAMP camp)
{
	_camp = camp;
}

CAMP Bullet::getCamp()
{
	return _camp;
}

void Bullet::hit(OtterEngine::Engine *oe)
{
	OtterEngine::SpritesManager::getInstance()->removeSprite(_sprite);
	oe->removeObject(oe->getIndex(this));
}

void Bullet::updateEvents(OtterEngine::Engine *oe)
{
	for (int i = 0; i < _events.size(); i++)
	{
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}
