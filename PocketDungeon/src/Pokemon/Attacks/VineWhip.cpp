//
// Created by flav on 1/24/19.
//

#include <OtterEngine/TimeManager.hpp>
#include <OtterEngine/SpriteManager/FixedSprite.hpp>
#include <OtterEngine/SpriteManager/AnimatedSprite.hpp>
#include <math.h>
#include "VineWhip.h"

#define PI 3.14159265

VineWhip::VineWhip(Pokemon *host)
	: Attack("vinewhip", 45, 100, 6.25, DamageType::PHYSICAL, Types::GRASS, host, 100)
{
	_launchTime = TimeManager::getInstance()->getTotalTime();
	//_name += "VineWhip::";
}

VineWhip::VineWhip(Attack *atk, Vector2d velocity, Vector2d pos)
		: Object(), Attack(atk, velocity, pos)
{
	_launchTime = TimeManager::getInstance()->getTotalTime();
	init();
	_name += "VineWhip::";
	_atkName = "vinewhip";
	addEvent<VineWhip>(_events, OtterEngine::Event<VineWhip>("Fade", &VineWhip::fadeReaction, &VineWhip::fadeVerification));
	addEvent<VineWhip>(_events, OtterEngine::Event<VineWhip>("Collide", &VineWhip::collideReaction, &VineWhip::collideVerification));
	_hitbox.setType(OtterEngine::Hitbox::SQUARE);
	_hitbox.setSquareSize(Vector2d(50, 200));
	_sprite = new OtterEngine::AnimatedSprite(this);
	_sprite->loadSpriteFromFile("ressources/lightning.png", 6, 6, 1, 1);
	OtterEngine::SpritesManager::getInstance()->addSprite(3, _sprite);
}

Attack *VineWhip::clone(Attack *atk, Vector2d velocity, Vector2d pos)
{
	return new VineWhip(atk, velocity, pos);
}

VineWhip::~VineWhip()
{

}

void VineWhip::init()
{
	double angle = _host->getAngleShot() + 90;

	_hitbox.setAngle(angle - 90);
	_hitbox.setPos(Vector2d(_host->getPos().x + 100 * cos(angle * PI / 180), _host->getPos().y + 100 * sin(angle * PI / 180)));
	_host->setVelocity(Vector2d(0, 0));
}

bool VineWhip::collideVerification(OtterEngine::Engine *oe)
{
	return Attack::collideVerification(oe);
}

int VineWhip::collideReaction(OtterEngine::Engine *oe)
{
	_host->setVelocity(Vector2d(0,0));
	return Attack::collideReaction(oe);
}

bool VineWhip::fadeVerification(OtterEngine::Engine *oe)
{
	float elapsedTime = TimeManager::getInstance()->getTotalTime();

	if(_hitbox.getSquareSize().y < 350) {
		_hitbox.setSquareSize(Vector2d(_hitbox.getSquareSize().x, _hitbox.getSquareSize().y + 1));
		_hitbox.setPos(Vector2d(getPos().x + 2 * cos((_hitbox.getAngle() + 90) * PI / 180), getPos().y + 2 * sin((_hitbox.getAngle() + 90) * PI / 180)));
	}
	_host->setInertness(true);
	_host->setVelocity(Vector2d(0, 0));
	if (_launchTime > elapsedTime || elapsedTime - _launchTime > 3.0 / 2.0) {
		return true;
	}
	return false;
}

int VineWhip::fadeReaction(OtterEngine::Engine *oe)
{
	_host->setVelocity(Vector2d(0, 0));
	return Attack::fadeReaction(oe);
}

void VineWhip::updateEvents(OtterEngine::Engine *oe)
{
	for (std::size_t i = 0; i < _events.size(); i++) {
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}

