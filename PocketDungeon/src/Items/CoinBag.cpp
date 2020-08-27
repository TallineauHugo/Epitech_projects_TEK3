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
#include "CoinBag.hpp"
#include "Event.hpp"

CoinBag::CoinBag()
: IItems() {
	_name += "CoinBag::";
	std::cout << "COIN_BAG\n";

	addEvent<CoinBag>(_events, OtterEngine::Event<CoinBag>("Time", &CoinBag::TimeReaction, &CoinBag::TimeVerification));
	addEvent<CoinBag>(_events, OtterEngine::Event<CoinBag>("Collide", &CoinBag::collideReaction, &CoinBag::collideVerification));

	_hitbox.setType(OtterEngine::Hitbox::CIRCLE);
	_hitbox.setRadius(25);

	_sprite = new OtterEngine::FixedSprite(this);
	_sprite->loadSpriteFromFile("ressources/texture/coin_bag.png");
	OtterEngine::SpritesManager::getInstance()->addSprite(2, _sprite);
	_launchTime = TimeManager::getInstance()->getTotalTime();
}

CoinBag::~CoinBag() {

}

bool CoinBag::TimeVerification(OtterEngine::Engine *oe) {
	if (_launchTime + 30 < TimeManager::getInstance()->getTotalTime())
		return true;
	return false;
}

int CoinBag::TimeReaction(OtterEngine::Engine *oe) {
	OtterEngine::SpritesManager::getInstance()->removeSprite(_sprite);
	oe->removeObject(oe->getIndex(this));
}

bool CoinBag::collideVerification(OtterEngine::Engine *oe)
{
	std::size_t i = oe->getIndex(this);
	std::map<int, int> cols = oe->getCols();
	auto objs = oe->getObjs();
	std::size_t amount = rand() % 6 + 5;

	for (std::map<int, int>::iterator it = cols.begin(); it != cols.end() && it->first <= i; ++it) {
		if (it->first == i && dynamic_cast<Player *>(objs[it->second]) != nullptr) {
			dynamic_cast<Player *>(objs[it->second])->gainCoin(amount);
			return true;
		}
		else if (it->second == i && dynamic_cast<Player *>(objs[it->first]) != nullptr) {
			dynamic_cast<Player *>(objs[it->first])->gainCoin(amount);
			return true;
		}
	}
	return false;
}

int CoinBag::collideReaction(OtterEngine::Engine *oe)
{
	OtterEngine::SpritesManager::getInstance()->removeSprite(_sprite);
	oe->removeObject(oe->getIndex(this));
}

void CoinBag::updateEvents(OtterEngine::Engine *oe)
{
	for (std::size_t i = 0; i < _events.size(); i++) {
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}