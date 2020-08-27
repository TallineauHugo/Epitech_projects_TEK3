//
// EPITECH PROJECT, 2019
// pocket dungeon
// File description:
// exp bag
//

#pragma once

#include "IItems.hpp"

class Coin : public virtual IItems {
public:
	Coin();
	~Coin();
public:
	bool TimeVerification(OtterEngine::Engine *oe);
	int TimeReaction(OtterEngine::Engine *oe);
	bool collideVerification(OtterEngine::Engine *oe);
	int collideReaction(OtterEngine::Engine *oe);

	void updateEvents(OtterEngine::Engine *oe);
private:
	std::vector<OtterEngine::Event<Coin>> _events;
};