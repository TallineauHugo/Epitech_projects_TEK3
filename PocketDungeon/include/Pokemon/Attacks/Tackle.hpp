//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// tackle
//

#pragma once

#include "Attack.hpp"

class Pokemon;

class Tackle : public virtual Attack
{
public:
	Tackle(Pokemon *host);

	Tackle(Attack *atk, Vector2d velocity, Vector2d pos);
	Attack *clone(Attack *atk, Vector2d velocity, Vector2d pos);

	~Tackle();

	bool fadeVerification(OtterEngine::Engine *oe);
	bool collideVerification(OtterEngine::Engine *oe);
	int fadeReaction(OtterEngine::Engine *oe);
	int collideReaction(OtterEngine::Engine *oe);

	void updateEvents(OtterEngine::Engine *oe);
private:
	void init();

	std::vector<OtterEngine::Event<Tackle>> _events;
};
