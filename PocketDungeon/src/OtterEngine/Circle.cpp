#include "Circle.hpp"
#include <iostream>

OtterEngine::Circle::Circle(Vector2d pos, int radius) : OtterEngine::Object()
{
	_name += "Circle::";
	_hitbox.setPos(pos);
	_hitbox.setAngle(0);
	_hitbox.setType(OtterEngine::Hitbox::CIRCLE);
	_hitbox.setRadius(radius);
}

OtterEngine::Circle::~Circle()
{

}

void OtterEngine::Circle::updateEvents(OtterEngine::Engine *oe)
{
	for (int i = 0; i < _events.size(); i++)
	{
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}
