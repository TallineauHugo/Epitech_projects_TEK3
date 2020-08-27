#include <iostream>
#include "EnnemySpaceShip.hpp"
#include "Event.hpp"
#include "ZigZagEnnemy.hpp"

ZigZagEnnemy::ZigZagEnnemy(Vector2d pos) : EnnemySpaceShip(pos, 25, 1), SpaceShip(pos, 0, ENNEMY)
{
	_name += "ZigZagEnnemy::";
	_velocity.x = -200;
	_topPos = pos.y - 150;
	_botPos = pos.y + 150;
	_hitbox.setSquareSize(Vector2d(50, 50));
	addEvent<ZigZagEnnemy>(_events, OtterEngine::Event<ZigZagEnnemy>("Collide", &ZigZagEnnemy::collision, &ZigZagEnnemy::collide));
	addEvent<ZigZagEnnemy>(_events, OtterEngine::Event<ZigZagEnnemy>("limit", &ZigZagEnnemy::GoDownReaction, &ZigZagEnnemy::GoDownVerification));
	addEvent<ZigZagEnnemy>(_events, OtterEngine::Event<ZigZagEnnemy>("Always", &ZigZagEnnemy::alwaysGoDown, &ZigZagEnnemy::always));
	_sprite = new OtterEngine::AnimatedSprite(this);
	_sprite->loadSpriteFromFile("ressources/texture/Wall.png");
}

ZigZagEnnemy::~ZigZagEnnemy()
{

}

EnnemySpaceShip *ZigZagEnnemy::clone()
{
        return (new ZigZagEnnemy(getPos()));
}

bool ZigZagEnnemy::collide(OtterEngine::Engine *oe)
{
	return CollisionVerification(oe);
}

int ZigZagEnnemy::collision(OtterEngine::Engine *oe)
{
	CollisionReaction(oe);
	oe->addObject(new ZigZagEnnemy(Vector2d(2000, getPos().y)));
}

bool ZigZagEnnemy::always(OtterEngine::Engine *oe)
{
	return true;
}

int ZigZagEnnemy::alwaysGoDown(OtterEngine::Engine *oe)
{
	_velocity.y += 2;
}

int ZigZagEnnemy::alwaysGoUp(OtterEngine::Engine *oe)
{
	_velocity.y -= 2;	
}

bool ZigZagEnnemy::GoDownVerification(OtterEngine::Engine *oe)
{
	if (getPos().y > _botPos)
		return true;
}

bool ZigZagEnnemy::GoUpVerification(OtterEngine::Engine *oe)
{
	if (getPos().y < _topPos)
		return true;
}

int ZigZagEnnemy::GoDownReaction(OtterEngine::Engine *oe)
{
	_velocity.y = 0;
	removeEvent(_events, "Always");
	addEvent<ZigZagEnnemy>(_events, OtterEngine::Event<ZigZagEnnemy>("Always", &ZigZagEnnemy::alwaysGoUp, &ZigZagEnnemy::always));
	removeEvent(_events, "limit");
	addEvent<ZigZagEnnemy>(_events, OtterEngine::Event<ZigZagEnnemy>("limit", &ZigZagEnnemy::GoUpReaction, &ZigZagEnnemy::GoUpVerification));
}

int ZigZagEnnemy::GoUpReaction(OtterEngine::Engine *oe)
{
	_velocity.y = 0;
	removeEvent(_events, "Always");
	addEvent<ZigZagEnnemy>(_events, OtterEngine::Event<ZigZagEnnemy>("Always", &ZigZagEnnemy::alwaysGoDown, &ZigZagEnnemy::always));
	removeEvent(_events, "limit");
	addEvent<ZigZagEnnemy>(_events, OtterEngine::Event<ZigZagEnnemy>("limit", &ZigZagEnnemy::GoDownReaction, &ZigZagEnnemy::GoDownVerification));
}

void ZigZagEnnemy::updateEvents(OtterEngine::Engine *oe)
{
	for (int i = 0; i < _events.size(); i++)
	{
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}

extern "C"
{
	__attribute__((constructor)) void constructor(void)
	{
	}

	__attribute__((destructor)) void destructor(void)
	{
	}

	EnnemySpaceShip* entryPoint()
	{
		return (new ZigZagEnnemy(Vector2d(0, 0)));
	}
}
