#include "CooldownReduc.hpp"

CooldownReduc::CooldownReduc(Vector2d pos)
{
	_name += "CooldownReduc";
	_hitbox.setType(OtterEngine::Hitbox::SQUARE);
	_hitbox.setSquareSize(Vector2d(40, 40));
	_hitbox.setPos(pos);
	_sprite->loadSpriteFromFile("ressources/texture/Wall.png");
}

CooldownReduc::~CooldownReduc()
{
	
}

void CooldownReduc::updateEvents(OtterEngine::Engine *oe)
{
	for (int i = 0; i < _events.size(); i++)
	{
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}
