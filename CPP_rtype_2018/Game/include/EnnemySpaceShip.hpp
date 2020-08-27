#pragma once

#include "SpaceShip.hpp"

class EnnemySpaceShip : public virtual SpaceShip
{
public:
	EnnemySpaceShip(Vector2d pos, int vue, int threat);
	~EnnemySpaceShip();

	virtual EnnemySpaceShip *clone();
	bool CollisionVerification(OtterEngine::Engine *);
	int CollisionReaction(OtterEngine::Engine *);

	int getThreat();

	void updateEvents(OtterEngine::Engine *);
private:
	int _value;
	int _threat;
	std::vector<OtterEngine::Event<EnnemySpaceShip>> _events;
};
