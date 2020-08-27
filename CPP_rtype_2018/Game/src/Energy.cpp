#include "Energy.hpp"

Energy::Energy(Vector2d pos, int value) : Object()
{
	_name += "Energy::";
	_hitbox.setType(OtterEngine::Hitbox::CIRCLE);
	_hitbox.setPos(pos);
	_hitbox.setRadius(value / 2);
	_sprite->loadSpriteFromFile("ressources/texture/Player.png");
}

Energy::~Energy()
{
	
}

int Energy::getValue()
{
	return _value;
}

void Energy::updateEvents(OtterEngine::Engine *oe)
{
	for (int i = 0; i < _events.size(); i++)
	{
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}
