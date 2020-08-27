//
// EPITECH PROJECT, 2019
// pocket dungeon
// File description:
// exp bag
//

#pragma once

#include "IItems.hpp"

class CoinBag : public virtual IItems {
public:
	CoinBag();
	~CoinBag();
public:
	bool TimeVerification(OtterEngine::Engine *oe);
	int TimeReaction(OtterEngine::Engine *oe);
	bool collideVerification(OtterEngine::Engine *oe);
	int collideReaction(OtterEngine::Engine *oe);

	void updateEvents(OtterEngine::Engine *oe);
private:
	std::vector<OtterEngine::Event<CoinBag>> _events;
};