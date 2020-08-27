#include "Bullet.hpp"

#pragma once

class Explosion : public virtual Bullet
{
public:
	Explosion(Vector2d pos, int size, CAMP camp, std::size_t id);
	~Explosion();

	bool isFinished(OtterEngine::Engine *);
	int Finish(OtterEngine::Engine *);
	virtual void hit(OtterEngine::Engine*);

	void updateEvents(OtterEngine::Engine *);
private:
	float moment;
	std::vector<OtterEngine::Event<Explosion>> _events;
};
