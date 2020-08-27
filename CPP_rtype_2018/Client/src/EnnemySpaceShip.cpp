#include <iostream>
#include "EnnemySpaceShip.hpp"
#include "Energy.hpp"
#include "Bullet.hpp"
#include "Id.hpp"
#include "AnimatedSprite.hpp"

EnnemySpaceShip::EnnemySpaceShip(Vector2d pos, int energy, std::size_t id) : Object(id), SpaceShip(pos, 0, ENNEMY, id), _value(energy)
{
	_name += "EnnemySpaceShip::";
	_sprite = new OtterEngine::AnimatedSprite(this);
	_sprite->loadSpriteFromFile("ressources/texture/enemy_spaceship.png", 8, 8, 1, 1);
	OtterEngine::SpritesManager::getInstance()->addSprite(1, _sprite);
}

EnnemySpaceShip::~EnnemySpaceShip()
{

}

bool EnnemySpaceShip::CollisionVerification(OtterEngine::Engine *oe)
{
	int i = oe->getIndex(this);
	std::map<int, int> cols = oe->getCols();
	auto objs = oe->getObjs();
	for(std::map<int,int>::iterator it = cols.begin(); it != cols.end() && it->first <= i; ++it){
		if ((it->first == i && ((objs[it->second]->getName().find("Bullet") != std::string::npos && dynamic_cast<Bullet *>(objs[it->second])->getCamp() == ALLY)
					|| (objs[it->second]->getName().find("SpaceShip") != std::string::npos && dynamic_cast<SpaceShip *>(objs[it->second])->getCamp() == ALLY)))
		    || (it->second == i && ((objs[it->first]->getName().find("Bullet") != std::string::npos && dynamic_cast<Bullet *>(objs[it->first])->getCamp() == ALLY)
					    || (objs[it->first]->getName().find("SpaceShip") != std::string::npos && dynamic_cast<SpaceShip *>(objs[it->first])->getCamp() == ALLY))))
		{
			if (objs[it->second]->getName().find("Bullet") != std::string::npos)
				dynamic_cast<Bullet *>(objs[it->second])->hit(oe);
			else if(objs[it->first]->getName().find("Bullet") != std::string::npos)
				dynamic_cast<Bullet *>(objs[it->first])->hit(oe);
			return true;
		}
	}
	return false;
}

int EnnemySpaceShip::CollisionReaction(OtterEngine::Engine *oe)
{
	OtterEngine::SpritesManager::getInstance()->removeSprite(_sprite);
	oe->removeObjectById(getId());
	oe->addObject(new Energy(getPos(), _value, Id::getInstance()->getNextId()));
	return 0;
}

void EnnemySpaceShip::updateEvents(OtterEngine::Engine *oe)
{
	for (std::size_t i = 0; i < _events.size(); i++)
	{
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}
