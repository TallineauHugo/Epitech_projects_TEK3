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
#include "Coin.hpp"
#include "Event.hpp"

Coin::Coin()
: IItems() {
	std::cout << "COIN\n";
	_name += "Coin::";

	addEvent<Coin>(_events, OtterEngine::Event<Coin>("Time", &Coin::TimeReaction, &Coin::TimeVerification));
	addEvent<Coin>(_events, OtterEngine::Event<Coin>("Collide", &Coin::collideReaction, &Coin::collideVerification));

	_hitbox.setType(OtterEngine::Hitbox::CIRCLE);
	_hitbox.setRadius(15);

	_sprite = new OtterEngine::FixedSprite(this);
	_sprite->loadSpriteFromFile("ressources/texture/coin.png");
	OtterEngine::SpritesManager::getInstance()->addSprite(2, _sprite);
	_launchTime = TimeManager::getInstance()->getTotalTime();
}

Coin::~Coin() {

}

bool Coin::TimeVerification(OtterEngine::Engine *oe) {
	if (_launchTime + 30 < TimeManager::getInstance()->getTotalTime())
		return true;
	return false;
}

int Coin::TimeReaction(OtterEngine::Engine *oe) {
	OtterEngine::SpritesManager::getInstance()->removeSprite(_sprite);
	oe->removeObject(oe->getIndex(this));
}

bool Coin::collideVerification(OtterEngine::Engine *oe)
{
	std::size_t i = oe->getIndex(this);
	std::map<int, int> cols = oe->getCols();
	auto objs = oe->getObjs();

	for (std::map<int, int>::iterator it = cols.begin(); it != cols.end() && it->first <= i; ++it) {
		if (it->first == i && dynamic_cast<Player *>(objs[it->second]) != nullptr) {
			dynamic_cast<Player *>(objs[it->second])->gainCoin(1);
			return true;
		}
		else if (it->second == i && dynamic_cast<Player *>(objs[it->first]) != nullptr) {
			dynamic_cast<Player *>(objs[it->first])->gainCoin(1);
			return true;
		}
	}
	return false;
}

int Coin::collideReaction(OtterEngine::Engine *oe)
{
	OtterEngine::SpritesManager::getInstance()->removeSprite(_sprite);
	oe->removeObject(oe->getIndex(this));
}

void Coin::updateEvents(OtterEngine::Engine *oe)
{
	for (std::size_t i = 0; i < _events.size(); i++) {
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}