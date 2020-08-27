#include <iostream>
#include "Bomb.hpp"
#include "Explosion.hpp"

Bomb::Bomb(Vector2d pos, Vector2d velocity, CAMP camp) : Bullet(pos, velocity, camp)
{
	_name += "Bomb::";
}

Bomb::~Bomb()
{

}

void Bomb::updateEvents(OtterEngine::Engine *oe)
{
	for (int i = 0; i < _events.size(); i++)
	{
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}

void Bomb::hit(OtterEngine::Engine *oe)
{
	std::cout << "lolilo\n";
	oe->addObject(new Explosion(getPos(), 350, _camp));
	Bullet::hit(oe);
}
