//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// tackle
//

#pragma once

#include "Attack.hpp"

class Pokemon;

class Growl : public virtual Attack
{
public:
	Growl(Pokemon *host);
	Growl(Attack *atk, Vector2d velocity, Vector2d pos);
	Attack *clone(Attack *atk, Vector2d velocity, Vector2d pos);
	~Growl();

	bool fadeVerification(OtterEngine::Engine *oe);
	bool collideVerification(OtterEngine::Engine *oe);
	int fadeReaction(OtterEngine::Engine *oe);
	int collideReaction(OtterEngine::Engine *oe);

	void updateEvents(OtterEngine::Engine *oe);
private:
	void init();

	float _launchTime;
	std::vector<OtterEngine::Event<Growl>> _events;
};
