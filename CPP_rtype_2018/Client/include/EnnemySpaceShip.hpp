#pragma once

#include "SpaceShip.hpp"

class EnnemySpaceShip : public virtual SpaceShip
{
public:
	EnnemySpaceShip(Vector2d pos, int vue, std::size_t id = 0);
	~EnnemySpaceShip();
	bool CollisionVerification(OtterEngine::Engine *);
	int CollisionReaction(OtterEngine::Engine *);

	void updateEvents(OtterEngine::Engine *);
private:
	int _value;
	std::vector<OtterEngine::Event<EnnemySpaceShip>> _events;
};
