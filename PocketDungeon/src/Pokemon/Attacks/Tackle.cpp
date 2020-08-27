//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// tackle
//

#include <iostream>
#include "FixedSprite.hpp"
#include "Tackle.hpp"
#include "Types.hpp"
#include "Pokemon.hpp"
#include <math.h>

#define PI 3.14159265

Tackle::Tackle(Pokemon *host)
	: Attack("tackle", 35, 95, 6.25, DamageType::PHYSICAL, Types::NORMAL, host, 300)
{
	//_name += "Tackle::";
}


Tackle::Tackle(Attack *atk, Vector2d velocity, Vector2d pos)
        : Object(), Attack(atk, velocity, pos)
{
	init();
	_name += "Tackle::";
	_atkName = "tackle";
	addEvent<Tackle>(_events, OtterEngine::Event<Tackle>("Fade", &Tackle::fadeReaction, &Tackle::fadeVerification));
	addEvent<Tackle>(_events, OtterEngine::Event<Tackle>("Collide", &Tackle::collideReaction, &Tackle::collideVerification)); 
	_hitbox.setType(OtterEngine::Hitbox::SQUARE);
	_hitbox.setSquareSize(Vector2d(100, 20));
	_sprite = new OtterEngine::FixedSprite(this);
	_sprite->loadSpriteFromFile("ressources/Tackle.png");
	OtterEngine::SpritesManager::getInstance()->addSprite(3, _sprite);
}

Attack *Tackle::clone(Attack *atk, Vector2d velocity, Vector2d pos)
{
	return new Tackle(atk, velocity, pos);
}

Tackle::~Tackle()
{}

void Tackle::init()
{
	double angle = _host->getAngleShot() + 90;
       
	_hitbox.setAngle(angle - 90);
	_hitbox.setPos(Vector2d(_host->getPos().x + 40 * cos(angle * PI / 180), _host->getPos().y + 40 * sin(angle * PI / 180)));
	_velocity = Vector2d(1000 * cos(angle * PI / 180), 1000 * sin(angle * PI / 180));
	//_host->setVelocity(Vector2d(1000 * cos(angle * PI / 180), 1000 * sin(angle * PI / 180)));
	_aim = Vector2d(getPos().x + 500 * cos(angle * PI / 180), getPos().y + 500 * sin(angle * PI / 180));
	_host->setInertness(true);
}

bool Tackle::collideVerification(OtterEngine::Engine *oe)
{
	return Attack::collideVerification(oe);
}

int Tackle::collideReaction(OtterEngine::Engine *oe)
{
	_host->setVelocity(Vector2d(250 * cos((_host->getAngleShot() - 90) * PI / 180), 250 * sin((_host->getAngleShot() - 90) * PI / 180)));
	return Attack::collideReaction(oe);
}

bool Tackle::fadeVerification(OtterEngine::Engine *oe)
{
	_host->setVelocity(Vector2d(1000 * cos((_host->getAngleShot() + 90) * PI / 180), 1000 * sin((_host->getAngleShot() + 90) * PI / 180)));
	return Attack::fadeVerification(oe);
}

int Tackle::fadeReaction(OtterEngine::Engine *oe)
{
	_host->setVelocity(Vector2d(0, 0));
	return Attack::fadeReaction(oe);	
}

void Tackle::updateEvents(OtterEngine::Engine *oe)
{
	for (std::size_t i = 0; i < _events.size(); i++) {
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}
