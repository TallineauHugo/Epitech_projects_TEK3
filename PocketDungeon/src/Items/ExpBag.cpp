//
// EPITECH PROJECT, 2019
// pocket dungeon
// File description:
// exp bag
//

#include "OtterEngine/TimeManager.hpp"
#include "Player.hpp"
#include "OtterEngine/SpriteManager/FixedSprite.hpp"
#include <iostream>
#include "ExpBag.hpp"
#include "Event.hpp"

ExpBag::ExpBag()
: IItems() {
	_name += "ExpBag::";

	addEvent<ExpBag>(_events, OtterEngine::Event<ExpBag>("Time", &ExpBag::TimeReaction, &ExpBag::TimeVerification));
	addEvent<ExpBag>(_events, OtterEngine::Event<ExpBag>("Collide", &ExpBag::collideReaction, &ExpBag::collideVerification));

	_hitbox.setType(OtterEngine::Hitbox::CIRCLE);
	_hitbox.setRadius(15);

	_sprite = new OtterEngine::FixedSprite(this);
	_sprite->loadSpriteFromFile("ressources/ExpBag.png");
	OtterEngine::SpritesManager::getInstance()->addSprite(2, _sprite);
	_launchTime = TimeManager::getInstance()->getTotalTime();
}

ExpBag::~ExpBag() {

}

bool ExpBag::TimeVerification(OtterEngine::Engine *oe) {
	if (_launchTime + 30 < TimeManager::getInstance()->getTotalTime())
		return true;
	return false;
}

int ExpBag::TimeReaction(OtterEngine::Engine *oe) {
	OtterEngine::SpritesManager::getInstance()->removeSprite(_sprite);
	oe->removeObject(oe->getIndex(this));
}

bool ExpBag::collideVerification(OtterEngine::Engine *oe)
{
	std::size_t i = oe->getIndex(this);
	std::map<int, int> cols = oe->getCols();
	auto objs = oe->getObjs();

	for (std::map<int, int>::iterator it = cols.begin(); it != cols.end() && it->first <= i; ++it) {
		if (it->first == i && dynamic_cast<Player *>(objs[it->second]) != nullptr) {
			return dynamic_cast<Player *>(objs[it->second])->gainExp(500);
		}
		else if (it->second == i && dynamic_cast<Player *>(objs[it->first]) != nullptr) {
			return dynamic_cast<Player *>(objs[it->first])->gainExp(500);
		}
	}
	return false;
}

int ExpBag::collideReaction(OtterEngine::Engine *oe)
{
	OtterEngine::SpritesManager::getInstance()->removeSprite(_sprite);
	oe->removeObject(oe->getIndex(this));
}

void ExpBag::updateEvents(OtterEngine::Engine *oe)
{
	for (std::size_t i = 0; i < _events.size(); i++) {
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}