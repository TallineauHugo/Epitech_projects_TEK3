//
// Created by flav on 1/24/19.
//

#ifndef POCKETDUNGEON_VINEWHIP_H
#define POCKETDUNGEON_VINEWHIP_H

#include "Attack.hpp"
#include <math.h>

class Pokemon;

class VineWhip : public virtual Attack
{
public:
	VineWhip(Pokemon *host);
	VineWhip(Attack *atk, Vector2d velocity, Vector2d pos);
	Attack *clone(Attack *atk, Vector2d velocity, Vector2d pos);
	~VineWhip();

	bool fadeVerification(OtterEngine::Engine *oe);
	bool collideVerification(OtterEngine::Engine *oe);
	int fadeReaction(OtterEngine::Engine *oe);
	int collideReaction(OtterEngine::Engine *oe);

	void updateEvents(OtterEngine::Engine *oe);
private:
	void init();

	float _launchTime;
	std::vector<OtterEngine::Event<VineWhip>> _events;
};

#endif //POCKETDUNGEON_VINEWHIP_H
