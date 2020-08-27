#pragma once

#include "Object.hpp"
#include "Camp.hpp"

class Bullet : public virtual OtterEngine::Object
{
public:
	Bullet(Vector2d pos, Vector2d velocity, CAMP camp, std::size_t id);
	~Bullet();
	
	void setCamp(CAMP);
	CAMP getCamp();
	bool outOfScreenVerification(OtterEngine::Engine *);
	int outOfScreenReaction(OtterEngine::Engine *);
	virtual void hit(OtterEngine::Engine *);
	void updateEvents(OtterEngine::Engine*);
	
protected:
	CAMP _camp;

private:
	std::vector<OtterEngine::Event<Bullet>> _events;
};
