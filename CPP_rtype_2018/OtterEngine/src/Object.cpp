#include "Object.hpp"
#include "ISprite.hpp"
#include "TimeManager.hpp"
#include "SpritesManager.hpp"
#include "FixedSprite.hpp"
#include <iostream>

OtterEngine::Object::Object(std::size_t id) : _velocity(0, 0), _id(id)
{
	_name = "::";
	_sprite = new OtterEngine::FixedSprite(this);
	//OtterEngine::SpritesManager::getInstance()->addSprite(1, _sprite);
}

OtterEngine::Object::~Object()
{
}

void OtterEngine::Object::setAim(Vector2d aim)
{
	_aim = aim;
}

Vector2d &OtterEngine::Object::getAim()
{
	return _aim;
}

std::size_t OtterEngine::Object::getId() const
{
	return _id;
}

void OtterEngine::Object::setPos(Vector2d pos)
{
	_hitbox.setPos(pos);
}

void OtterEngine::Object::setHitBox(OtterEngine::Hitbox hitbox)
{
	_hitbox = hitbox;
}

void OtterEngine::Object::setVelocity(Vector2d velocity)
{
	_velocity = velocity;
}

Vector2d &OtterEngine::Object::getPos()
{
	return _hitbox.getPos();
}

Vector2d OtterEngine::Object::getSize()
{
	if (this->_hitbox.getType() == Hitbox::CIRCLE)
		return {(double)this->_hitbox.getRadius() * 2, (double)this->_hitbox.getRadius() * 2};
	else if (this->_hitbox.getType() == Hitbox::SQUARE)
		return this->_hitbox.getSquareSize();
	else
		return {0, 0};
}

OtterEngine::Hitbox OtterEngine::Object::getHitbox()
{
	return _hitbox;
}

void OtterEngine::Object::setAngle(int angle)
{
	_hitbox.setAngle(angle);
}

int OtterEngine::Object::getAngle()
{
	return (_hitbox.getAngle());
}

Vector2d &OtterEngine::Object::getVelocity()
{
	return _velocity;
}

void OtterEngine::Object::applyVelocity()
{
	TimeManager *timeManager = TimeManager::getInstance();
	Vector2d move(this->_velocity.x * timeManager->getDeltaTime(), this->_velocity.y * timeManager->getDeltaTime());

	this->_hitbox.setPos(this->_hitbox.getPos() + move);
}

void OtterEngine::Object::updateEvents(OtterEngine::Engine *oe)
{
	for (std::size_t i = 0; i < _events.size(); i++)
	{
		if (_events[i].verification(oe, *this))
		    _events[i].reaction(oe, *this);
	}
}

std::string OtterEngine::Object::getName()
{
	return this->_name;
}

OtterEngine::ISprite *OtterEngine::Object::getSprite()
{
	return this->_sprite;
}