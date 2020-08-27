#include <iostream>
#include "Bomb.hpp"
#include "Explosion.hpp"
#include "Id.hpp"

Bomb::Bomb(Vector2d pos, Vector2d velocity, CAMP camp, std::size_t id) : Object(id), Bullet(pos, velocity, camp, id)
{
	_name += "Bomb::";
}

Bomb::~Bomb()
{

}

void Bomb::updateEvents(OtterEngine::Engine *oe)
{
	for (int i = 0; (std::size_t)i < _events.size(); i++)
	{
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}

void Bomb::hit(OtterEngine::Engine *oe)
{
	std::cout << "lolilol\n";
	oe->addObject(new Explosion(getPos(), 350, _camp, Id::getInstance()->getNextId()));
	Bullet::hit(oe);
}
