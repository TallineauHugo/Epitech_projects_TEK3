#include <iostream>
#include "EnnemySpaceShip.hpp"
#include "Event.hpp"
#include "ZigZagEnnemy.hpp"
#include "Id.hpp"

ZigZagEnnemy::ZigZagEnnemy(Vector2d pos, std::size_t id) : Object(id), SpaceShip(pos, 0, ENNEMY, id), EnnemySpaceShip(pos, 25, id)
{
	_name += "ZigZagEnnemy::";
	_velocity.x = -200;
	_topPos = pos.y - 150;
	_botPos = pos.y + 150;
	_hitbox.setSquareSize(Vector2d(50, 50));
	addEvent<ZigZagEnnemy>(_events, OtterEngine::Event<ZigZagEnnemy>("Collide", &ZigZagEnnemy::collision, &ZigZagEnnemy::collide));
	addEvent<ZigZagEnnemy>(_events, OtterEngine::Event<ZigZagEnnemy>("limit", &ZigZagEnnemy::GoDownReaction, &ZigZagEnnemy::GoDownVerification));
	addEvent<ZigZagEnnemy>(_events, OtterEngine::Event<ZigZagEnnemy>("Always", &ZigZagEnnemy::alwaysGoDown, &ZigZagEnnemy::always));
	_sprite->loadSpriteFromFile("ressources/texture/Wall.png");
}

ZigZagEnnemy::~ZigZagEnnemy()
{

}

bool ZigZagEnnemy::collide(OtterEngine::Engine *oe)
{
	return CollisionVerification(oe);
}

int ZigZagEnnemy::collision(OtterEngine::Engine *oe)
{
	CollisionReaction(oe);
	oe->addObject(new ZigZagEnnemy(Vector2d(2000, getPos().y), Id::getInstance()->getNextId()));
	return 0;
}

bool ZigZagEnnemy::always(OtterEngine::Engine *oe)
{
	(void)oe;
	return true;
}

int ZigZagEnnemy::alwaysGoDown(OtterEngine::Engine *oe)
{
	(void)oe;
	_velocity.y += 2;
	return 0;
}

int ZigZagEnnemy::alwaysGoUp(OtterEngine::Engine *oe)
{
	(void)oe;
	_velocity.y -= 2;	
	return 0;
}

bool ZigZagEnnemy::GoDownVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	if (getPos().y > _botPos)
		return true;
	return false;
}

bool ZigZagEnnemy::GoUpVerification(OtterEngine::Engine *oe)
{
	(void)oe;
	if (getPos().y < _topPos)
		return true;
	return false;
}

int ZigZagEnnemy::GoDownReaction(OtterEngine::Engine *oe)
{
	(void)oe;
	_velocity.y = 0;
	removeEvent(_events, "Always");
	addEvent<ZigZagEnnemy>(_events, OtterEngine::Event<ZigZagEnnemy>("Always", &ZigZagEnnemy::alwaysGoUp, &ZigZagEnnemy::always));
	removeEvent(_events, "limit");
	addEvent<ZigZagEnnemy>(_events, OtterEngine::Event<ZigZagEnnemy>("limit", &ZigZagEnnemy::GoUpReaction, &ZigZagEnnemy::GoUpVerification));
	return 0;
}

int ZigZagEnnemy::GoUpReaction(OtterEngine::Engine *oe)
{
	(void)oe;
	_velocity.y = 0;
	removeEvent(_events, "Always");
	addEvent<ZigZagEnnemy>(_events, OtterEngine::Event<ZigZagEnnemy>("Always", &ZigZagEnnemy::alwaysGoDown, &ZigZagEnnemy::always));
	removeEvent(_events, "limit");
	addEvent<ZigZagEnnemy>(_events, OtterEngine::Event<ZigZagEnnemy>("limit", &ZigZagEnnemy::GoDownReaction, &ZigZagEnnemy::GoDownVerification));
	return 0;
}

void ZigZagEnnemy::updateEvents(OtterEngine::Engine *oe)
{
	for (std::size_t i = 0; i < _events.size(); i++)
	{
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}
