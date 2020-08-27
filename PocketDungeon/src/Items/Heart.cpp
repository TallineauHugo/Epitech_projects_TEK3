//
// Created by flav on 1/31/19.
//

#include <OtterEngine/TimeManager.hpp>
#include "Player.hpp"
#include <OtterEngine/SpriteManager/FixedSprite.hpp>
#include <iostream>
#include "Heart.hpp"
#include "Event.hpp"

Heart::Heart()
: IItems() {
	_name += "Heart::";

	addEvent<Heart>(_events, OtterEngine::Event<Heart>("Time", &Heart::TimeReaction, &Heart::TimeVerification));
	addEvent<Heart>(_events, OtterEngine::Event<Heart>("Collide", &Heart::collideReaction, &Heart::collideVerification));

	_hitbox.setType(OtterEngine::Hitbox::CIRCLE);
	_hitbox.setRadius(15);

	_sprite = new OtterEngine::FixedSprite(this);
	_sprite->loadSpriteFromFile("ressources/heart.png");
	OtterEngine::SpritesManager::getInstance()->addSprite(2, _sprite);
	_launchTime = TimeManager::getInstance()->getTotalTime();
}

Heart::~Heart() {

}

bool Heart::TimeVerification(OtterEngine::Engine *oe) {
	if (_launchTime + 15 < TimeManager::getInstance()->getTotalTime())
		return true;
	return false;
}

int Heart::TimeReaction(OtterEngine::Engine *oe) {
	OtterEngine::SpritesManager::getInstance()->removeSprite(_sprite);
	oe->removeObject(oe->getIndex(this));
}

bool Heart::collideVerification(OtterEngine::Engine *oe)
{
	std::size_t i = oe->getIndex(this);
	std::map<int, int> cols = oe->getCols();
	auto objs = oe->getObjs();

	for (std::map<int, int>::iterator it = cols.begin(); it != cols.end() && it->first <= i; ++it) {
		if (it->first == i && dynamic_cast<Player *>(objs[it->second]) != nullptr) {
			return dynamic_cast<Player *>(objs[it->second])->heal(10);
		}
		else if (it->second == i && dynamic_cast<Player *>(objs[it->first]) != nullptr) {
			return dynamic_cast<Player *>(objs[it->first])->heal(10);
		}
	}
	return false;
}

int Heart::collideReaction(OtterEngine::Engine *oe)
{
	OtterEngine::SpritesManager::getInstance()->removeSprite(_sprite);
	oe->removeObject(oe->getIndex(this));
}

void Heart::updateEvents(OtterEngine::Engine *oe)
{
	for (std::size_t i = 0; i < _events.size(); i++) {
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}