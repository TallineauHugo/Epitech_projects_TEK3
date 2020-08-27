//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// tackle
//

#include <iostream>
#include "FixedSprite.hpp"
#include "Growl.hpp"
#include "Types.hpp"
#include "Pokemon.hpp"
#include "TimeManager.hpp"
#include <math.h>

#define PI 3.14159265

Growl::Growl(Pokemon *host)
	: Attack("growl", 0, 100, 0, DamageType::NEUTRAL, Types::NONE, host, 0)
{
	_launchTime = TimeManager::getInstance()->getTotalTime();
	_name += "Growl::";
}

Growl::Growl(Attack *atk, Vector2d velocity, Vector2d pos)
        : Object(), Attack(atk, velocity, pos)
{
	_launchTime = TimeManager::getInstance()->getTotalTime();
	init();
	_name += "Growl::";
	_atkName = "growl";
	addEvent<Growl>(_events, OtterEngine::Event<Growl>("Fade", &Growl::fadeReaction, &Growl::fadeVerification));
	addEvent<Growl>(_events, OtterEngine::Event<Growl>("Collide", &Growl::collideReaction, &Growl::collideVerification)); 
	_hitbox.setType(OtterEngine::Hitbox::CIRCLE);
	_hitbox.setRadius(0);
	_sprite = new OtterEngine::FixedSprite(this);
	_sprite->loadSpriteFromFile("ressources/Onde.png");
	OtterEngine::SpritesManager::getInstance()->addSprite(3, _sprite);
}

Attack *Growl::clone(Attack *atk, Vector2d velocity, Vector2d pos)
{
	return new Growl(atk, velocity, pos);
}


Growl::~Growl()
{
	
}

void Growl::init()
{
	double angle = _host->getHitbox().getAngle() + 90;
	
	_hitbox.setAngle(angle - 90);
	_hitbox.setPos(Vector2d(_host->getPos().x, _host->getPos().y));
}

bool Growl::collideVerification(OtterEngine::Engine *oe)
{
	std::size_t i = oe->getIndex(this);
	std::map<int, int> cols = oe->getCols();
	auto objs = oe->getObjs();

	for (std::map<int, int>::iterator it = cols.begin(); it != cols.end() && it->first <= i; ++it) {
		if (it->first == i && dynamic_cast<Pokemon *>(objs[it->second]) != nullptr && objs[it->second] != _host) {
			dynamic_cast<Pokemon *>(objs[it->second])->applyStatusFor(Status::ATKDEBUFF, 10);
			return true;
		}
		else if (it->second == i && dynamic_cast<Pokemon *>(objs[it->first]) != nullptr && objs[it->first] != _host) {
			dynamic_cast<Pokemon *>(objs[it->first])->applyStatusFor(Status::ATKDEBUFF, 10);
			return true;
		}
	}
	return false;
}

int Growl::collideReaction(OtterEngine::Engine *oe)
{
	//Attack::collideReaction(oe);
}

bool Growl::fadeVerification(OtterEngine::Engine *oe)
{
	float elapsedTime = TimeManager::getInstance()->getTotalTime();

	_hitbox.setPos(Vector2d(_host->getPos().x, _host->getPos().y));
	if (_hitbox.getRadius() < 300)
		_hitbox.setRadius(_hitbox.getRadius() + 2);
	if (_launchTime > elapsedTime || elapsedTime - _launchTime > 0.5) {
		return true;
	}
	return false;
}

int Growl::fadeReaction(OtterEngine::Engine *oe)
{
	return Attack::fadeReaction(oe);	
}

void Growl::updateEvents(OtterEngine::Engine *oe)
{
	for (std::size_t i = 0; i < _events.size(); i++) {
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}
