#include "Object.hpp"
#include "define.hpp"

#pragma once

class Square : public virtual OtterEngine::Object
{
public:
	Square(Vector2d pos, int side);
	~Square();
	bool colision(OtterEngine::Engine *oe);
	int block(OtterEngine::Engine *oe);
	std::vector<OtterEngine::Event<Square>> getEvents(){return _events;}
	virtual void updateEvents(OtterEngine::Engine *);	
private:
	
	std::vector<OtterEngine::Event<Square>> _events;
};
