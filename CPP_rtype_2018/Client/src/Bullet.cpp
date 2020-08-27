#include <iostream>
#include "Object.hpp"
#include "Bullet.hpp"
#include "Camp.hpp"
#include "Hitbox.hpp"
#include "AnimatedSprite.hpp"
#include "WindowManager.hpp"

Bullet::Bullet(Vector2d pos, Vector2d velocity, CAMP camp, std::size_t id) : Object(id), _camp(camp)
{	
	_hitbox.setPos(pos);
	_velocity = velocity;
	_name += "Bullet::";
	_hitbox.setType(OtterEngine::Hitbox::SQUARE);
	_hitbox.setSquareSize(Vector2d(20, 20));
	_sprite = new OtterEngine::AnimatedSprite(this);
	_sprite->loadSpriteFromFile("ressources/texture/bullet.png", 8, 8, 1, 1);
	OtterEngine::SpritesManager::getInstance()->addSprite(1, _sprite);
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
	for (std::size_t i = 0; i < _events.size(); i++)
	{
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}
