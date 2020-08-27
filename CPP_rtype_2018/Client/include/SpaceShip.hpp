#pragma once

#include "Camp.hpp"
#include "Object.hpp"

class SpaceShip : public virtual OtterEngine::Object
{
public:
	
	SpaceShip(Vector2d pos, float maxCooldown, CAMP camp, std::size_t id);
	~SpaceShip();

	virtual int shootBullet(OtterEngine::Engine *oe);
	float getCooldown();
	void setCooldown(float cooldown);
	CAMP getCamp();
	void setCamp(CAMP camp);
	virtual void updateEvents(OtterEngine::Engine *oe);
	
protected:
	float _lastShoot;
	float _cooldown;
	CAMP _camp;

private:
	std::vector<OtterEngine::Event<SpaceShip>> _events;
};	
