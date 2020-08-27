#pragma once

#include "EnnemySpaceShip.hpp"

class ShootingEnnemy : public virtual EnnemySpaceShip
{
public:
	
	ShootingEnnemy(Vector2d pos);
	~ShootingEnnemy();
	virtual EnnemySpaceShip *clone();

	bool collide(OtterEngine::Engine *);
	int collision(OtterEngine::Engine *);
	
	bool always(OtterEngine::Engine *);
	int shoot(OtterEngine::Engine *);
	
	void updateEvents(OtterEngine::Engine*);
private:
	std::vector<OtterEngine::Event<ShootingEnnemy>> _events;
};
