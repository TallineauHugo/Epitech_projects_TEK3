#include "Energy.hpp"
#include "FixedSprite.hpp"
#include <iostream>
Energy::Energy(Vector2d pos, int value, std::size_t id) : Object(id), _value(value)
{
	_name += "Energy::";
	_hitbox.setType(OtterEngine::Hitbox::CIRCLE);
	_hitbox.setPos(pos);
	_hitbox.setRadius(value / 2);
	_sprite = new OtterEngine::FixedSprite(this);
	_sprite->loadSpriteFromFile("ressources/texture/Player.png");
		OtterEngine::SpritesManager::getInstance()->addSprite(1, _sprite);
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
	for (std::size_t i = 0; i < _events.size(); i++)
	{
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}
