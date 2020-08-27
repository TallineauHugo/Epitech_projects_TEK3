//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// tackle
//

#include <iostream>
#include "AnimatedSprite.hpp"
#include "ThunderShock.hpp"
#include "Types.hpp"
#include "Pokemon.hpp"
#include "TimeManager.hpp"
#include "InputManager.hpp"
#include <math.h>

#define PI 3.14159265

ThunderShock::ThunderShock(Pokemon *host)
	: Attack("thundershock", 40, 100, 6.25, DamageType::SPECIAL, Types::ELECTRIC, host, 200)
{
	_launchTime = TimeManager::getInstance()->getTotalTime();
	//_name += "ThunderShock::";
}

ThunderShock::ThunderShock(Attack *atk, Vector2d velocity, Vector2d pos)
        : Object(), Attack(atk, velocity, pos)
{
	_launchTime = TimeManager::getInstance()->getTotalTime();
	init();
	_name += "ThunderShock::";
	_atkName = "thundershock";
	addEvent<ThunderShock>(_events, OtterEngine::Event<ThunderShock>("Fade", &ThunderShock::fadeReaction, &ThunderShock::fadeVerification));
	addEvent<ThunderShock>(_events, OtterEngine::Event<ThunderShock>("Collide", &ThunderShock::collideReaction, &ThunderShock::collideVerification)); 
	_hitbox.setType(OtterEngine::Hitbox::SQUARE);
	_hitbox.setSquareSize(Vector2d(50, 0));
	_sprite = new OtterEngine::AnimatedSprite(this);
	_sprite->loadSpriteFromFile("ressources/lightning.png", 6, 6, 1, 1);
	OtterEngine::SpritesManager::getInstance()->addSprite(3, _sprite);
}

Attack *ThunderShock::clone(Attack *atk, Vector2d velocity, Vector2d pos)
{
	return new ThunderShock(atk, velocity, pos);
}

ThunderShock::~ThunderShock()
{

}

void ThunderShock::init()
{
	double angle = _host->getAngleShot() + 90;
       
	_hitbox.setAngle(angle - 90);
	_hitbox.setPos(Vector2d(_host->getPos().x + 1 * cos(angle * PI / 180), _host->getPos().y + 1 * sin(angle * PI / 180)));
	_host->setVelocity(Vector2d(0, 0));
	_host->startAttack();

	angle -= 90;
	if (angle < 0)
		angle += 360;
	if (angle >= 0 && angle < 90)
		_host->setFacing(DOWN);
	else if (angle >= 90 && angle < 135)
		_host->setFacing(LEFT);
	else if (angle >= 135 && angle < 270)
		_host->setFacing(UP);
	else if (angle >= 270 && angle < 315)
		_host->setFacing(RIGHT);
	else
		_host->setFacing(DOWN);
	
	/*switch ((int)(angle - 90)) {
		case 0:
			_host->setFacing(DOWN);
			break;
		case 45:
			_host->setFacing(DOWN);
			break;
		case 90:
			_host->setFacing(LEFT);
			break;
		case 135:
			_host->setFacing(UP);
			break;
		case 180:
			_host->setFacing(UP);
			break;
		case 225:
			_host->setFacing(UP);
			break;
		case 270:
			_host->setFacing(RIGHT);
			break;
		case 315:
			_host->setFacing(DOWN);
			break;
		
	}*/
}

bool ThunderShock::collideVerification(OtterEngine::Engine *oe)
{
	return Attack::collideVerification(oe);
}

int ThunderShock::collideReaction(OtterEngine::Engine *oe)
{
	_host->setVelocity(Vector2d(0,0));
	_host->stopAttack();
	return Attack::collideReaction(oe);
}

bool ThunderShock::fadeVerification(OtterEngine::Engine *oe)
{
	float elapsedTime = TimeManager::getInstance()->getTotalTime();

	if(_hitbox.getSquareSize().y < 200) {
		_hitbox.setSquareSize(Vector2d(_hitbox.getSquareSize().x, _hitbox.getSquareSize().y + 3));
		_hitbox.setPos(Vector2d(getPos().x + 2 * cos((_hitbox.getAngle() + 90) * PI / 180), getPos().y + 2 * sin((_hitbox.getAngle() + 90) * PI / 180)));
	}
	_host->setInertness(true);
	_host->setVelocity(Vector2d(0, 0));
	if (_launchTime > elapsedTime || elapsedTime - _launchTime > 3.0 / 2.0) {
		return true;
	}
	return false;
}

int ThunderShock::fadeReaction(OtterEngine::Engine *oe)
{
	_host->setVelocity(Vector2d(0, 0));
	_host->stopAttack();
	return Attack::fadeReaction(oe);	
}

void ThunderShock::updateEvents(OtterEngine::Engine *oe)
{
	for (std::size_t i = 0; i < _events.size(); i++) {
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}
