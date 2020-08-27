#pragma once

#include "EnnemySpaceShip.hpp"

class ZigZagEnnemy : public virtual EnnemySpaceShip
{
public:
	
	ZigZagEnnemy(Vector2d pos);
	~ZigZagEnnemy();

	virtual EnnemySpaceShip *clone();
	bool collide(OtterEngine::Engine *);
	int collision(OtterEngine::Engine *);
	
	bool always(OtterEngine::Engine *);
	int alwaysGoDown(OtterEngine::Engine *);
	int alwaysGoUp(OtterEngine::Engine *);
	
	bool GoDownVerification(OtterEngine::Engine *);
	bool GoUpVerification(OtterEngine::Engine *);
	int GoDownReaction(OtterEngine::Engine *);
	int GoUpReaction(OtterEngine::Engine *);

	void updateEvents(OtterEngine::Engine*);
private:
	std::vector<OtterEngine::Event<ZigZagEnnemy>> _events;
	double _topPos;
	double _botPos;
};
