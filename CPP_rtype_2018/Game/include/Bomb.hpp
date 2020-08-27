#include "Bullet.hpp"

#pragma once

class Bomb : public virtual Bullet
{
public:
	Bomb(Vector2d pos, Vector2d velocity, CAMP camp);
	~Bomb();

	void updateEvents(OtterEngine::Engine*);
	virtual void hit(OtterEngine::Engine *);
	
private:
	std::vector<OtterEngine::Event<Bullet>> _events;
};
