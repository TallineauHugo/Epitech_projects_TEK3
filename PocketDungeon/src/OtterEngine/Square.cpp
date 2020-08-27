#include "Square.hpp"
#include "Event.hpp"
#include <iostream>

Square::Square(Vector2d pos, int side) : OtterEngine::Object()
{
	_name += "Square::";
	_hitbox.setPos(pos);
	_hitbox.setAngle(0);
	_hitbox.setType(OtterEngine::Hitbox::SQUARE);
	_hitbox.setSquareSize(Vector2d(side, side));
	_events.push_back(OtterEngine::Event<Square>("collision", &Square::block, &Square::colision));
}

Square::~Square()
{

}


bool Square::colision(OtterEngine::Engine *oe)
{
	std::cout << "lolilol" << std::endl;
	return true;
}

int Square::block(OtterEngine::Engine *oe)
{
	return 1;
	
}

void Square::updateEvents(OtterEngine::Engine *oe)
{
	for (int i = 0; i < _events.size(); i++)
	{
		if (_events[i].verification(oe, *this))
			_events[i].reaction(oe, *this);
	}
}

