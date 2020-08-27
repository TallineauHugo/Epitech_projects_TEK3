#include <iostream>
#include "EnnemySpaceShip.hpp"
#include "Energy.hpp"
#include "Bullet.hpp"
#include "CooldownReduc.hpp"

EnnemySpaceShip::EnnemySpaceShip(Vector2d pos, int energy, int threat) : SpaceShip(pos, 0, ENNEMY), _value(energy), _threat(threat)
{
	_name += "EnnemySpaceShip::";
}

EnnemySpaceShip::~EnnemySpaceShip()
{

}

EnnemySpaceShip *EnnemySpaceShip::clone()
{
	return (new EnnemySpaceShip(getPos(), _value, _threat));
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
	oe->removeObject(oe->getIndex(this));
	if (rand() % 3 == 0)
			oe->addObject(new CooldownReduc(getPos()));
	oe->addObject(new Energy(getPos(), _value));
}

void EnnemySpaceShip::updateEvents(OtterEngine::Engine *oe)
{
	for (int i = 0; i < _events.size(); i++)
	{
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}

int EnnemySpaceShip::getThreat()
{
	return _threat;
}
