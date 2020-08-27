//
// EPITECH PROJECT, 2018
// otter engine
// File description:
// pokemon factory
//

#pragma once

#include "Dungeon.hpp"

class DungeonFactory
{
public:
	static DungeonFactory *getInstance() {
		static DungeonFactory instance;

		return &instance;
	}
	~DungeonFactory();

	Dungeon *createDungeon(int level, OtterEngine::Engine *);
private:
	DungeonFactory();
};
